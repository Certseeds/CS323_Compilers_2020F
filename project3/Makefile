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
.lex: $(SRC_PATH)/lex.l
	@cd $(SRC_PATH);$(FLEX) lex.l
	@cd ./../
.syntax: $(SRC_PATH)/syntax.y
	@cd $(SRC_PATH);$(BISON) -t -d -v syntax.y
	@cd ./../
.prepare:.lex .syntax
.node: .prepare
	$(CPP) -c $(SRC_PATH)/node.cpp -o $(TEMP_PATH)/node.o
	@ar -rc $(TEMP_PATH)/libnode.a $(TEMP_PATH)/node.o
.yyerror: .prepare
	$(CPP) -c $(SRC_PATH)/yyerror_myself.cpp -o $(TEMP_PATH)/yyerror_myself.o
	@ar -rc $(TEMP_PATH)/libyyerror_myself.a $(TEMP_PATH)/yyerror_myself.o
.type: .prepare
	$(CPP) -c $(SRC_PATH)/type.cpp -o $(TEMP_PATH)/type.o
	@ar -rc $(TEMP_PATH)/libtype.a $(TEMP_PATH)/type.o
.semanticError: .prepare
	$(CPP) -c $(SRC_PATH)/semanticError.cpp -o $(TEMP_PATH)/semanticError.o
	@ar -rc $(TEMP_PATH)/libsemanticError.a $(TEMP_PATH)/semanticError.o
.visit: .prepare
	$(CPP) -c $(SRC_PATH)/visitSyntaxTree.cpp -o $(TEMP_PATH)/visitSyntaxTree.o
	@ar -rc $(TEMP_PATH)/libvisitSyntaxTree.a $(TEMP_PATH)/visitSyntaxTree.o
.interCode: .prepare
	$(CPP) -c $(SRC_PATH)/interCode.cpp -o $(TEMP_PATH)/interCode.o
	@ar -rc $(TEMP_PATH)/libinterCode.a $(TEMP_PATH)/interCode.o
.translate: .prepare
	$(CPP) -c $(SRC_PATH)/translate.cpp -o $(TEMP_PATH)/translate.o
	@ar -rc $(TEMP_PATH)/libtranslate.a $(TEMP_PATH)/translate.o
splc: .node .yyerror .type .semanticError .visit .translate .interCode
	@mkdir -p bin
	touch bin/splc
	@chmod +x bin/splc
	$(CPP) $(SRC_PATH)/main.cpp -static \
	-L./$(TEMP_PATH) -lnode -lyyerror_myself  \
    -lvisitSyntaxTree -lsemanticError -ltype -linterCode -ltranslate -o splc
	@cp ./splc ./bin/splc
clean:
	@rm -rf bin/ ./splc ./splc.out
.PHONY: splc clean