# --- Project settings ---
PROJECT := my_c_project

CC := gcc
STD_FLAGS := -Wall -Wextra -std=c11 -g
CFLAGS := $(STD_FLAGS) -O2
LDFLAGS := -lm

# Optional GTK (currently disabled)
GTK_CFLAGS :=
GTK_LIBS   :=

# Directories
SRC_DIR := src
INC_DIR := include
TEST_DIR := tests
BUILD_DIR := build
BIN_DIR := bin

INCLUDES := -I$(INC_DIR)

# --- Source files ---
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Main program object (exclude from test builds)
MAIN_OBJ := $(BUILD_DIR)/main.o
APP_OBJS := $(filter-out $(MAIN_OBJ),$(OBJ_FILES))

# --- Test files ---
TEST_SRC := $(wildcard $(TEST_DIR)/*_test.c)
TEST_OBJS := $(patsubst $(TEST_DIR)/%_test.c,$(BUILD_DIR)/%_test.o,$(TEST_SRC))

# --- Executables ---
MAIN_EXE := $(BIN_DIR)/$(PROJECT)
TEST_EXE := $(BIN_DIR)/$(PROJECT)_test


.PHONY: all run tests clean rebuild debug sanitize run_san


# Default target
all: $(MAIN_EXE)

run: $(MAIN_EXE)
	./$(MAIN_EXE)


# Create build/bin dirs when needed
$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@


# --- Main program build ---
$(MAIN_EXE): $(OBJ_FILES) | $(BIN_DIR)
	@echo "Linking main executable..."
	$(CC) $^ $(LDFLAGS) $(GTK_LIBS) -o $@


# --- Compile application sources ---
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $(INCLUDES) -c $< -o $@


# --- Test Build ---
test: $(TEST_EXE)
	@echo "Running tests..."
	./$(TEST_EXE)

$(TEST_EXE): $(APP_OBJS) $(TEST_OBJS) | $(BIN_DIR)
	@echo "Linking test runner..."
	$(CC) $^ -lcunit $(LDFLAGS) -o $@

$(BUILD_DIR)/%_test.o: $(TEST_DIR)/%_test.c | $(BUILD_DIR)
	@echo "Compiling test $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


# --- Cleaning ---
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

rebuild: clean all tests


# --- Debug build ---
debug:
	$(MAKE) CFLAGS='$(STD_FLAGS) -DDEBUG' rebuild


# --- Sanitized build ---
SAN_FLAGS := $(STD_FLAGS) -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
SAN_EXE := $(BIN_DIR)/$(PROJECT)_san

sanitize: $(SAN_EXE)

$(SAN_EXE): $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.san.o,$(SRC_FILES)) | $(BIN_DIR)
	$(CC) $^ $(SAN_FLAGS) $(LDFLAGS) $(GTK_LIBS) -o $@

$(BUILD_DIR)/%.san.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(SAN_FLAGS) $(GTK_CFLAGS) $(INCLUDES) -c $< -o $@

run_san: sanitize
	./$(SAN_EXE)

