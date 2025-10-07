# --- Configuration ---
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c11
LDFLAGS = -lm
# For debugging/optimization: -g or -O2
# CFLAGS += -g
# CFLAGS += -O2

# --- Directories and Files ---
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = test
BUILD_DIR = build
BIN_DIR = bin

# Source files
MAIN_SRCS = $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)

# Object files
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(MAIN_SRCS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/test_%.o,$(TEST_SRCS)) # Add prefix to test objects

# Executables
TARGET_EXEC = $(BIN_DIR)/app
TEST_EXEC = $(BIN_DIR)/run_tests


# --- Main Targets ---

.PHONY: all $(BUILD_DIR) $(BIN_DIR) clean test

# Default target: builds the main application
all: $(BUILD_DIR) $(BIN_DIR) $(TARGET_EXEC)

# Target to build and run tests
test: $(BUILD_DIR) $(BIN_DIR) $(TEST_EXEC)
	@echo "--- Running tests ---"
	@./$(TEST_EXEC)

# Target to build the main executable
$(TARGET_EXEC): $(MAIN_OBJS)
	@echo "Linking $@"
	$(CC) $(LDFLAGS) $^ -o $@

# Target to build the test executable
$(TEST_EXEC): $(MAIN_OBJS) $(TEST_OBJS)
	@echo "Linking $@"
	# Note: Link all app objects and test objects. You might need a testing framework library (e.g., -lcunit)
	$(CC) $(LDFLAGS) -lcunit $^ -o $@

# --- Compilation Rules ---

# Rule for building application objects (.o) from .c files in src/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for building test objects (.o) from .c files in test/
# We use a distinct name to avoid collision if a test file had the same name as a src file (e.g., main.c)
$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

# --- Utility Targets ---

# Create the build and bin directories if they don't exist
$(BUILD_DIR):
	@mkdir -p $@

$(BIN_DIR):
	@mkdir -p $@

# Clean up build and bin directories
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
