# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude -lncurses -lsqlite3

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN := flipd

# Find all .cpp files recursively
SRC := $(shell find $(SRC_DIR) -name '*.cpp')
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o,$(SRC))

# Default target
all: $(BIN)

# Link objects into final binary
$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp into .o (create subdirectories as needed)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN)
