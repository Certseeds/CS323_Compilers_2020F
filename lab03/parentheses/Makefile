CC=gcc --std=c11
FLEX=flex
BISON=bison

.PHONY: clean 

.lex: lex.l
	$(FLEX) lex.l
.syntax: syntax.y
	$(BISON) -t -d syntax.y
# parentheses: .lex .syntax
# 	$(CC) syntax.tab.c -lfl -ly -o parentheses.out
libparen: .lex .syntax
	$(CC) syntax.tab.c -lfl -ly -fPIC --shared -o libparen.so
clean:
	@rm -f lex.yy.c syntax.tab.* *.out *.so