
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
MAIN := main

OBJETOS := $(BUILD_DIR)/main.o $(BUILD_DIR)/tabuleiro.o $(BUILD_DIR)/I_UI.o $(BUILD_DIR)/peças.o
CXX := g++
CXXFLAGS := -std=c++17 -Wall -g

INCLUDE_DIRS := -I/usr/include -Iinclude
LIB_DIR := -L/usr/lib

LIBS := -lsfml-graphics -lsfml-window -lsfml-system

all: $(BIN_DIR)/$(MAIN)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $(SRC_DIR)/main.cpp -o $@

$(BUILD_DIR)/tabuleiro.o: $(SRC_DIR)/tabuleiro.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $(SRC_DIR)/tabuleiro.cpp -o $@

$(BUILD_DIR)/I_UI.o: $(SRC_DIR)/I_UI.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $(SRC_DIR)/I_UI.cpp -o $@

$(BUILD_DIR)/peças.o: $(SRC_DIR)/peças.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $(SRC_DIR)/peças.cpp -o $@

$(BIN_DIR)/$(MAIN): $(OBJETOS)
	$(CXX) $(OBJETOS) $(LIB_DIR) $(LIBS) -o $@

# CLEAN
clean:
	rm -rf $(BUILD_DIR)/*.o $(BIN_DIR)/$(MAIN)

.PHONY: all clean
