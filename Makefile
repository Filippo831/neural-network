# --- Makefile Template for C Project with CUnit ---

# Directories:
# - src/       : Main source files
# - include/   : Header files
# - tests/     : Test source files (must end with _test.c)
# - build/     : Intermediate object files (.o)
# - bin/       : Final executables
# - lib/       : Placeholder for external libraries (optional)


# Project Name (used for the final executable name)
PROJECT_NAME := my_c_project

# Compiler and standard flags
CC := gcc
STD_CFLAGS := -Wall -Wextra -std=c11 -g

# CFLAGS for release/optimized build
CFLAGS := $(STD_CFLAGS) -O2

# Directory paths
SRCDIR := src
INCLDIR := include
BUILDDIR := build
BINDIR := bin
TESTDIR := tests
LIBDIR := lib

# CUnit Linker and Include Flags
LDFLAGS_CUNIT := -lcunit

# Include search paths for headers
INCLUDES := -I$(INCLDIR)

# Standard Linker flags (e.g., -lm for math)
LDFLAGS := -lm


# Find all source files in the source directory
SRC_FILES := $(wildcard $(SRCDIR)/*.c)

# Define ALL object file paths in the build directory
OBJ_FILES := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRC_FILES))

# --- FIX FOR MULTIPLE MAIN DEFINITION ---
# 1. Identify the application's main object file (assuming src/main.c)
APP_MAIN_OBJECT := $(BUILDDIR)/main.o

# 2. Define the list of application objects needed for tests (ALL objects excluding main.o)
# This prevents the application's main() from conflicting with the test runner's main()
APP_TEST_OBJS := $(filter-out $(APP_MAIN_OBJECT), $(OBJ_FILES))
# --- END FIX ---

# Test-specific files
TEST_SRC_FILES := $(wildcard $(TESTDIR)/*_test.c)

# Define test object file paths (distinguished from main objects)
TEST_OBJ_FILES := $(patsubst $(TESTDIR)/%.c, $(BUILDDIR)/%.test.o, $(TEST_SRC_FILES))

# Executable names
MAIN_EXECUTABLE := $(BINDIR)/$(PROJECT_NAME)
TEST_RUNNER := $(BINDIR)/$(PROJECT_NAME)_test


.PHONY: all main tests clean rebuild dirs debug sanitize run_san

# Default target: builds the main executable
all: main

# Target to ensure build and bin directories exist (Prerequisite)
$(BUILDDIR) $(BINDIR):
	@mkdir -p $@


main: $(MAIN_EXECUTABLE)

run: ${MAIN_EXECUTABLE}
	@./$(MAIN_EXECUTABLE)

$(MAIN_EXECUTABLE): $(OBJ_FILES) | $(BINDIR)
	@echo "=================================================="
	@echo "Linking main executable: $@"
	$(CC) $^ $(LDFLAGS) -o $@

# Rule to compile main source files into objects
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@echo "Compiling main: $< -> $@"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@




# Test runner target: builds and runs the tests
tests: $(TEST_RUNNER)
	@echo "=================================================="
	@echo "Running tests with CUnit..."
	@./$(TEST_RUNNER)

# Linking the test runner: *** NOW USES APP_TEST_OBJS INSTEAD OF OBJ_FILES ***
$(TEST_RUNNER): $(APP_TEST_OBJS) $(TEST_OBJ_FILES) | $(BINDIR)
	@echo "Linking test runner: $@"
	$(CC) $^ $(LDFLAGS) $(LDFLAGS_CUNIT) -o $@

# Rule to compile test source files
$(BUILDDIR)/%.test.o: $(TESTDIR)/%.c | $(BUILDDIR)
	@echo "Compiling test: $< -> $@"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# --- 6. Utility Targets ---

clean:
	@echo "Cleaning build and bin directories..."
	@rm -rf $(BUILDDIR)
	@rm -rf $(BINDIR)

rebuild: clean all tests

# Target to build with debug flags enabled
debug:
	@echo "Starting debug build..."
	@make CFLAGS='$(STD_CFLAGS) -DDEBUG' clean all tests


SAN_CFLAGS := $(STD_CFLAGS) -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
SAN_EXECUTABLE := $(BINDIR)/$(PROJECT_NAME)_san

sanitize: $(SAN_EXECUTABLE)

run_san: sanitize
	@echo "=================================================="
	@echo "Running sanitized executable: $@"
	@./$(SAN_EXECUTABLE)

# Rule to compile ALL source files into objects with SANITIZER flags
# We use a pattern rule specific to the build directory for sanitized objects
$(BUILDDIR)/%.san.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@echo "Compiling sanitized: $< -> $@"
	$(CC) $(SAN_CFLAGS) $(INCLUDES) -c $< -o $@

# Define all sanitized object file paths
SAN_OBJ_FILES := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.san.o, $(SRC_FILES))

# Linking the sanitized main executable
$(SAN_EXECUTABLE): $(SAN_OBJ_FILES) | $(BINDIR)
	@echo "=================================================="
	@echo "Linking sanitized executable: $@"
	$(CC) $^ $(LDFLAGS) $(SAN_CFLAGS) -o $@
