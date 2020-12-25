GPP=g++
FLEX=flex
BISON=bison
MAKE_PATH = bin

CXX_STD= -std=c++17
CXX_DEBUG = -g
CXX_WARN = -Wall -Wextra
CXX_FLAGS = -O3 $(CXX_DEBUG) $(CXX_STD) $(CXX_WARN)
CPP = $(GPP) $(CXX_FLAGS)

.PHONY: clean

.lex:lex.l
	$(FLEX) lex.l
.syntax:syntax.y
	$(BISON) -t -d -v syntax.y
.prepare:.lex .syntax
.node: .prepare
	$(CPP) -c node.cpp -o node.o
	@ar -rc libnode.a node.o
.yyerror: .prepare
	$(CPP) -c yyerror_myself.cpp -o yyerror_myself.o
	@ar -rc libyyerror_myself.a yyerror_myself.o
.type: .prepare
	$(CPP) -c type.cpp -o type.o
	@ar -rc libtype.a type.o
.semanticError: .prepare
	$(CPP) -c semanticError.cpp -o semanticError.o
	@ar -rc libsemanticError.a semanticError.o
.visit: .prepare
	$(CPP) -c visitSyntaxTree.cpp -o visitSyntaxTree.o
	@ar -rc libvisitSyntaxTree.a visitSyntaxTree.o
splc: .node .yyerror .type .semanticError .visit
	$(CPP) main.cpp -static -L. -lnode -lyyerror_myself  \
    -lvisitSyntaxTree -lsemanticError -ltype  -o splc
clean:
	@rm -rf $(MAKE_PATH)/ lex.yy.c syntax.tab.* *.out *.o *.a *.so syntax.output splc