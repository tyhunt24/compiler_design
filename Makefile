default:
	clear
	flex -l flex.l
	bison -dv parser.y 
	gcc -o testProg.cmm parser.tab.c lex.yy.c -lfl
