CPP=g++
FLEX=flex
BISON=bison
CXXSTD = -std=c++17

CXXDEBUG = -g -Wall
SRC_PATH=src
CXXWARN = -Wall -Wextra
MAKE_PATH=./make-build-dir
CFLAGS = -O0 $(CXXDEBUG) $(CXXSTD) $(CXXWARN)

.lex:lex.l
	$(FLEX) lex.l
.syntax:syntax.y
	$(BISON) -t -d -v syntax.y
.node: .lex .syntax
	$(CPP) $(CFLAGS) -c node.cpp -o node.o
	@ar -rc libnode.a node.o
.yyerror: .lex .syntax
	$(CPP) $(CFLAGS) -c yyerror_myself.cpp -o yyerror_myself.o
	@ar -rc libyyerror_myself.a yyerror_myself.o
.parser: .lex .syntax
	$(CPP) $(CFLAGS) -c syntax.tab.c -o parser.o  -lfl -ly
	@ar -rc libparser.a parser.o
splc: .node .yyerror .parser
	$(CPP) $(CFLAGS) main.c -static -L. -lnode -lyyerror_myself -lparser -o splc
clean:
	@rm -rf $(MAKE_PATH)/ lex.yy.c syntax.tab.* *.out *.o *.a *.so syntax.output splc