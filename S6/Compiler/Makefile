all:	tokens.l grammar.y comp.c linker.l
	lex -i tokens.l
	lex -o linker.c linker.l 
	yacc grammar.y -d
	gcc y.tab.c lex.yy.c -g -o comp
	gcc linker.c -o linker
	./comp $(input)
	./linker

clean:
	rm comp lex.* linker linker.c output* *.xsm y.*
