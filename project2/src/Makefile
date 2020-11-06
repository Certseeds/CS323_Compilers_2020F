CPP=g++
FLEX=flex
BISON=bison
CXXSTD = -std=c++17

CXXDEBUG = -g
CXXWARN = -Wall -Wextra
MAKE_PATH=./make-build-dir
CXXFLAGS = -O3 $(CXXDEBUG) $(CXXSTD) $(CXXWARN)

.lex:lex.l
	$(FLEX) lex.l
.syntax:syntax.y
	$(BISON) -t -d -v syntax.y
.node: .lex .syntax
	$(CPP) $(CXXFLAGS) -c node.cpp -o node.o
	@ar -rc libnode.a node.o
.yyerror: .lex .syntax
	$(CPP) $(CXXFLAGS) -c yyerror_myself.cpp -o yyerror_myself.o
	@ar -rc libyyerror_myself.a yyerror_myself.o
.parser: .lex .syntax
	$(CPP) $(CXXFLAGS) -c syntax.tab.c -o parser.o  -lfl -ly
	@ar -rc libparser.a parser.o
splc: .node .yyerror .parser
	$(CPP) $(CXXFLAGS) main.cpp -static -L. -lnode -lyyerror_myself -lparser -o splc
clean:
	@rm -rf $(MAKE_PATH)/ lex.yy.c syntax.tab.* *.out *.o *.a *.so syntax.output splc