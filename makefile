# compiler and flags (for compiling and linking)
CXX := g++
PRE_FLAGS := -m64 -g -Wall -std=c++20
POST_FLAGS := -ldl

# directories
SRC_DIR := src
INC_DIR := include
BIN_DIR := bin
OBJ_DIR := $(BIN_DIR)/obj

# files
SRC := $(shell find $(SRC_DIR)/ -type f -iname "*.cpp")
OBJ := $(subst $(SRC_DIR),$(OBJ_DIR),$(foreach file,$(basename $(SRC)),$(file).o))
BIN_NAME := build
BIN := $(BIN_DIR)/$(BIN_NAME)

# === build tasks =========================================

all: $(BIN)

$(BIN): $(OBJ)
	@echo "linking..."
	@$(CXX) $(OBJ) -L$(LIB_DIR) $(POST_FLAGS) -o $(BIN)
	@echo "done :D"

.SECONDEXPANSION:

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $$(dir $$@)
	@echo "compiling $<..."
	@$(CXX) -c $< $(PRE_FLAGS) -I$(INC_DIR) -o $@

# ensure directories are created via custom task
%/:
	@mkdir -p $@

.PRECIOUS: %/

# === utility tasks =======================================

.PHONY: clean run setup

clean:
	@echo "cleaning project..."
	rm -rf $(BIN_DIR)/*
	@echo "project cleaned!"

run: $(BIN)
	@echo "running $(BIN)..."
	@cd $(BIN_DIR) && ./$(BIN_NAME)

# make dirs and create main file
setup:
	@echo "setting up project..."

	@echo "creating directories..."
	mkdir -p $(SRC_DIR) $(BIN_DIR) $(OBJ_DIR) $(INC_DIR)

	@echo "creating main.cpp..."
	@echo "#include <iostream>" >> $(SRC_DIR)/main.cpp
	@echo "" >> $(SRC_DIR)/main.cpp
	@echo "int main() {" >> $(SRC_DIR)/main.cpp
	@echo "	std::cout << \"hello world!!\n\";">> $(SRC_DIR)/main.cpp
	@echo "" >> $(SRC_DIR)/main.cpp
	@echo "	return 0;" >> $(SRC_DIR)/main.cpp
	@echo "}" >> $(SRC_DIR)/main.cpp

	@echo "set up project!!"
