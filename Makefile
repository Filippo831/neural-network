# --- Makefile for C Project with CUnit + GTK Support ---

# Project Name
PROJECT_NAME := my_c_project

# Compiler
CC := gcc

# Standard Flags
STD_CFLAGS := -Wall -Wextra -std=c11 -g

# Release Flags
CFLAGS := $(STD_CFLAGS) -O2

# Directories
SRCDIR := src
INCLDIR := include
BUILDDIR := build
BINDIR := bin
TESTDIR := tests
LIBDIR := lib

# Include paths
INCLUDES := -I$(INCLDIR)

# Standard linker flags
LDFLAGS := -lm

# CUnit
LDFLAGS_CUNIT := -lcunit

# --- GTK Support ---
GTK_CFLAGS := $(shell pkg-config --cflags gtk4)
GTK_LIBS   := $(shell pkg-config --libs gtk4)
# For GTK3 use:
# GTK_CFLAGS := $(shell pkg-config --cflags gtk+-3.0)
# GTK_LIBS   := $(shell pkg-config --libs gtk+-3.0)

# Source files
SRC_FILES := $(wildcard $(SRCDIR)/*.c)

# Object files
OBJ_FILES := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRC_FILES))

# Identify main.o
APP_MAIN_OBJECT := $(BUILDDIR)/main.o

# Non-main objects for tests
APP_TEST_OBJS := $(filter-out $(APP_MAIN_OBJECT), $(OBJ_FILES))

# Test sources
TEST_SRC_FILES := $(wildcard $(TESTDIR)/*_test.c)

# Test objects
TEST_OBJ_FILES := $(patsubst $(TESTDIR)/%.c, $(BUILDDIR)/%.test.o, $(TEST_SRC_FILES))

# Executables
MAIN_EXECUTABLE := $(BINDIR)/$(PROJECT_NAME)
TEST_RUNNER := $(BINDIR)/$(PROJECT_NAME)_test



.PHONY: all main tests clean rebuild debug sanitize run_san


# Default target
all: main

run: $(MAIN_EXECUTABLE)
	@./$(MAIN_EXECUTABLE)


# Ensure build/bin dirs exist
$(BUILDDIR) $(BINDIR):
	@mkdir -p $@


# --- Main executable ---
main: $(MAIN_EXECUTABLE)

$(MAIN_EXECUTABLE): $(OBJ_FILES) | $(BINDIR)
	@echo "Linking main executable: $@"
	$(CC) $^ $(LDFLAGS) $(GTK_LIBS) -o $@


# --- Compilation Rules (GTK-enabled) ---
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@echo "Compiling: $< -> $@"
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $(INCLUDES) -c $< -o $@



# --- Tests ---
tests: $(TEST_RUNNER)
	@echo "Running tests with CUnit..."
	@./$(TEST_RUNNER)

# Test runner (does NOT link GTK unless your sources require it)
$(TEST_RUNNER): $(APP_TEST_OBJS) $(TEST_OBJ_FILES) | $(BINDIR)
	@echo "Linking test runner: $@"
	$(CC) $^ $(LDFLAGS) $(LDFLAGS_CUNIT) -o $@

# Test object compilation
$(BUILDDIR)/%.test.o: $(TESTDIR)/%.c | $(BUILDDIR)
	@echo "Compiling test: $< -> $@"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@



# --- Cleaning and rebuilding ---
clean:
	@echo "Cleaning..."
	@rm -rf $(BUILDDIR) $(BINDIR)

rebuild: clean all tests



# --- Debug build with GTK ---
debug:
	@echo "DEBUG build..."
	@$(MAKE) CFLAGS='$(STD_CFLAGS) -DDEBUG' clean all tests



# --- Sanitizer Build ---
SAN_CFLAGS := $(STD_CFLAGS) -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
SAN_EXECUTABLE := $(BINDIR)/$(PROJECT_NAME)_san

sanitize: $(SAN_EXECUTABLE)

run_san: sanitize
	@echo "Running sanitized executable..."
	@./$(SAN_EXECUTABLE)

$(BUILDDIR)/%.san.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@echo "Compiling sanitized: $< -> $@"
	$(CC) $(SAN_CFLAGS) $(GTK_CFLAGS) $(INCLUDES) -c $< -o $@

SAN_OBJ_FILES := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.san.o, $(SRC_FILES))

$(SAN_EXECUTABLE): $(SAN_OBJ_FILES) | $(BINDIR)
	@echo "Linking sanitized executable: $@"
	$(CC) $^ $(LDFLAGS) $(GTK_LIBS) $(SAN_CFLAGS) -o $@

