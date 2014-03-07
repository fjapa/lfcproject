		bison -v -d -o sintatico.c sintatico.y

		flex -v -t lexico.l > lexico.c

		gcc sintatico.c lexico.c -o compilador
