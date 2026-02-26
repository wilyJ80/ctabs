# --- Configuration ---
CC := gcc
CFLAGS := -Wall -Wextra -g -Iinclude
SRC_DIR := src
TEST_DIR := test
BUILD_DIR := build
BIN := $(BUILD_DIR)/ctabs
TEST_BIN := $(BUILD_DIR)/tests

# --- Files ---
SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_SRCS))

# Main OBJS without main() for testing, adjust as needed
APP_OBJS := $(filter-out $(BUILD_DIR)/main.o, $(OBJS))

# --- Rules ---
.PHONY: all clean test

all: $(BIN)

# Link executable
$(BIN): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Test Setup (Links APP_OBJS with TEST_SRCS)
test: $(TEST_BIN)
	@./$(TEST_BIN)

$(TEST_BIN): $(APP_OBJS) $(TEST_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
