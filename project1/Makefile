CC=gcc
FLEX=flex
BISON=bison
pwd=pwd
CSTD = -std=c11

CDEBUG = -g -Wall

CWARN = -Wall -Wextra

CFLAGS = -O0 $(CDEBUG) $(CSTD) $(CWARN)
.lex: lex.l
	$(FLEX) lex.l
.syntax: syntax.y
	$(BISON) -t -d -v syntax.y
.node: .lex .syntax
	$(CC) $(CFLAGS) -c node.c -o node.o
	@ar -rc libnode.a node.o
.yyerror: .lex .syntax
	$(CC) $(CFLAGS) -c yyerror_myself.c -o yyerror_myself.o
	@ar -rc libyyerror_myself.a yyerror_myself.o
.parser: .lex .syntax
	$(CC) $(CFLAGS) -c syntax.tab.c -o parser.o  -lfl -ly
	@ar -rc libparser.a parser.o
splc: .node .yyerror .parser
	@mkdir bin
	@touch bin/splc
	@chmod +0755 bin/splc
	$(CC) $(CFLAGS) main.c -static -L. -lnode -lyyerror_myself -lparser -o bin/splc

clean:
	@rm -rf bin/ lex.yy.c syntax.tab.* *.out *.o *.a *.so syntax.output