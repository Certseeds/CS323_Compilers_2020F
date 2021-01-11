CC=gcc
BIN=bin
SRC=main.cpp tac.cpp mips32.cpp

GPP=g++
FLEX=flex
BISON=bison
SRC_PATH=./src
TEMP_PATH=cmake-build-debug

CXX_STD= -std=c++17
CXX_DEBUG = -g
CXX_WARN = -Wall -Wextra
CXX_HEADERS = -I./include
CXX_FLAGS = -O3 $(CXX_DEBUG) $(CXX_STD) $(CXX_WARN) $(CXX_HEADERS)
CPP = $(GPP) $(CXX_FLAGS)

splc: clean
	@mkdir -p $(BIN)
	$(CC) $(SRC) -o $(BIN)/$@
clean:
	@rm -rf $(BIN)
.PHONY: clean
