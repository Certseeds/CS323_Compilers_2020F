CC=gcc
FLEX=flex
BISON=bison


.lex: lex.l
	$(FLEX) lex.l
.syntax: syntax.y
	$(BISON) -t -d -v syntax.y
splc: .lex .syntax
	@mkdir bin
	touch bin/splc
	@chmod +0755 bin/splc
	$(CC)  -std=c11 -Wall -Wextra syntax.tab.c -lfl -ly -o bin/splc 
clean:
	@rm -rf bin/ lex.yy.c syntax.tab.* *.out *.so syntax.output