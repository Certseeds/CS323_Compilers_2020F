CPP=g++
FLEX=flex
BISON=bison


CXXSTD = -std=c++17
CXXWARN = -Wall -Wextra  
CXXDEBUG = -g
CXXFLAGS = -O3 $(CXXDEBUG) $(CXXSTD) $(CXXWARN)

.PHONY: clean 

.lex: lex.l
	$(FLEX) lex.l
.syntax: syntax.y
	$(BISON) -t -d -v syntax.y
.parser: .lex .syntax
	$(CPP) $(CXXFLAGS) -c syntax.tab.c -o parser.o  -lfl -ly
	@ar -rc libparser.a parser.o
.Object:
	$(CPP) $(CXXFLAGS) -c Object.cpp -o jsonobject.o
	@ar -rc libjsonobject.a jsonobject.o
main: .lex .syntax .parser .Object
	$(CPP) $(CXXFLAGS) main.cpp -static -L. -lparser -ljsonobject -o Object.out

clean:
	@rm -f lex.yy.c syntax.tab.* *.out *.a *.o syntax.output