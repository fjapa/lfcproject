%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treenodes.h"
#include "sintatico.h"
int level, erro=0;
%}

%option noyywrap

ID [a-zA-Z]+
NUM [0-9][0-9]*
OPERADORES "+"|"-"|"*"|"/"|"<"|"<="|">"|">="|"=="|"!="|"="|";"|","|"("|")"|"["|"]"|"{"|"}"
STR ["][^"]*[^\n]["]

%x COMENT
%%
"/*"			{
			BEGIN( COMENT );
			level = 1;
			}


<COMENT>"/*"		{
			level++;
			}


<COMENT>"*/" 		{
			if(--level == 0){
				BEGIN( INITIAL );}
			else{
				erro++;}
			}

<COMENT>.|\n|\r 	{
			}

<<EOF>>		  	{ 
			if(erro>0){
				printf("ERRO LÉXICO! Comentário desbalanceado.\n");}
		    	yyterminate();
		 	}

"string"	{ return STRING; }
"else"		{ return ELSE; }
"if"		{ return IF; }
"int"		{ return INT; }
"return"	{ return RETURN; }
"void"		{ return VOID; }
"while"		{ return WHILE; }
"+"		{ return MAIS; }
"-"		{ return MENOS; }
"*"		{ return ASTERISCO; }
"/"		{ return BARRA; }
"<"		{ return MENOR; }
"<="		{ return MENORIGUAL; }
">"		{ return MAIOR; }
">="		{ return MAIORIGUAL; }
"=="		{ return IGUALIGUAL; }
"!="		{ return DIFERENTE; }
"="		{ return IGUAL; }
";"		{ return PONTOVIRGULA; }
","		{ return VIRGULA; }
"("		{ return ABREPARENTESES; }
")"		{ return FECHAPARENTESES; }
"["		{ return ABRECOLCHETE; }
"]"		{ return FECHACOLCHETE; }
"{"		{ return ABRECHAVE; }
"}"		{ return FECHACHAVE; }
{ID}		{ yylval.str = strdup(yytext); return ID; }
{NUM}*		{ yylval.digito = atoi(yytext); return DIGITO; }
{STR} 		{ yylval.str = strdup(yytext); return CADEIASTRING; }
{ID}{NUM}({ID}|{NUM})*	{ printf("ERRO LÉXICO! ID Inválido.\n");}
{NUM}{ID}({ID}|{NUM})*	{ printf("ERRO LÉXICO! ID Inválido.\n");}

.|\n|\r

%%
/*
int main(void)
{
yylex();
return 0;
}
*/
