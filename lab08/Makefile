GPP=g++
FLEX=flex
BISON=bison


CXX_STD = -std=c++17
CXX_WARN = -Wall -Wextra
CXX_DEBUG = -g
CXX_FLAGS = -O3 $(CXX_DEBUG) $(CXX_STD) $(CXX_WARN)
CPP = $(GPP) $(CXX_FLAGS)

.PHONY: clean

.lex: lex.l
	$(FLEX) lex.l
.syntax: syntax.y
	$(BISON) -t -d -v syntax.y
.parser: .lex .syntax
	$(CPP) -c syntax.tab.c -o parser.o  -lfl -ly
	@ar -rc libparser.a parser.o
.Object:
	$(CPP) -c Object.cpp -o jsonobject.o
	@ar -rc libjsonobject.a jsonobject.o
main: .lex .syntax .parser .Object
	$(CPP) main.cpp -static -L. -lparser -ljsonobject -o jc.out

clean:
	@rm -f lex.yy.c syntax.tab.* *.out *.a *.o syntax.output