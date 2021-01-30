GPP=g++
FLEX=flex
BISON=bison
TEMP_PATH=cmake-build-debug

CXX_STD= -std=c++17
CXX_DEBUG = -g
CXX_WARN = -Wall -Wextra
CXX_HEADERS =
CXX_FLAGS = -O3 $(CXX_DEBUG) $(CXX_STD) $(CXX_WARN) $(CXX_HEADERS)
CPP = $(GPP) $(CXX_FLAGS)
pre_all_task: clean
tac: tac.cpp tac.hpp clean
	$(CPP) -c tac.cpp -o tac.o
	@ar -rc libtac.a tac.o

mips32: mips32.cpp mips32.hpp clean
	$(CPP) -c mips32.cpp -o mips32.o
	@ar -rc libmips32.a mips32.o

splc: tac mips32
	@mkdir -p ./bin
	$(CPP) main.cpp -static -L./ -ltac -lmips32  -o splc
	@mv ./splc ./bin/splc
	@rm -rf *.o *.a
clean:
	@rm -rf ./bin *.o *.a
.PHONY: clean
