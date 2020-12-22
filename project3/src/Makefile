CPP=g++
FLEX=flex
BISON=bison
MAKE_PATH = bin

CXXSTD= -std=c++17
CXXDEBUG = -g
CXXWARN = -Wall -Wextra
CXXFLAGS = -O3 $(CXXDEBUG) $(CXXSTD) $(CXXWARN)

.PHONY: clean

.lex:lex.l
	$(FLEX) lex.l
.syntax:syntax.y
	$(BISON) -t -d -v syntax.y
.prepare:.lex .syntax
.node: .prepare
	$(CPP) $(CXXFLAGS) -c node.cpp -o node.o
	@ar -rc libnode.a node.o
.yyerror: .prepare
	$(CPP) $(CXXFLAGS) -c yyerror_myself.cpp -o yyerror_myself.o
	@ar -rc libyyerror_myself.a yyerror_myself.o
.type: .prepare
	$(CPP) $(CXXFLAGS) -c type.cpp -o type.o
	@ar -rc libtype.a type.o
.semanticError: .prepare
	$(CPP) $(CXXFLAGS) -c semanticError.cpp -o semanticError.o
	@ar -rc libsemanticError.a semanticError.o
.visit: .prepare
	$(CPP) $(CXXFLAGS) -c visitSyntaxTree.cpp -o visitSyntaxTree.o
	@ar -rc libvisitSyntaxTree.a visitSyntaxTree.o
.interCode: .prepare
	$(CPP) $(CXXFLAGS) -c interCode.cpp -o interCode.o
	@ar -rc libinterCode.a interCode.o
.translate: .prepare
	$(CPP) $(CXXFLAGS) -c translate.cpp -o translate.o
	@ar -rc libtranslate.a translate.o
splc: .node .yyerror .type .semanticError .visit .translate .interCode
	$(CPP) $(CXXFLAGS) main.cpp -static -L. -lnode -lyyerror_myself  \
    -lvisitSyntaxTree -lsemanticError -ltype -linterCode -ltranslate -o splc

clean:
	@rm -rf $(MAKE_PATH)/ lex.yy.c syntax.tab.* *.out *.o *.a *.so syntax.output splc