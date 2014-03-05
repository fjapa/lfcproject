%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treenodes.h"
#include "sintatico_bison.h"
int level;
%}

%option noyywrap
OPERADORES "+"|"-"|"*"|"/"|"<"|"<="|">"|">="|"=="|"!="|"="|";"|","|"("|")"|"["|"]"|"{"|"}"
ID [a-zA-Z]+
IDINVALIDO [0-9]+[a-zA-Z]+[0-9]*|[0-9]*[a-zA-Z]+[0-9]+
NUM [0-9][0-9]*
STR ["][^"]*[^\n]["]
INVALIDO (.)

%x COMENT

%%
\r|\n|\t
"/*" BEGIN( COMENT ); level = 1; printf( "Início do comentário:\n");

<COMENT>{
"/*" {level++; printf( "/*");}
"*/" {if(--level == 0){ BEGIN( INITIAL ); printf( "\nFim do comentário!\n");} else{ printf( "*/"); }}
\n {ECHO;}
}

"string"	{ return STRING; }
"else"		{ return ELSE; }
"if"		  { return IF; }
"int"		  { return INT; }
"return"	{ return RETURN; }
"void"		{ return VOID; }
"while"		{ return WHILE; }
"+"		    { return MAIS; }
"-"		    { return MENOS; }
"*"		    { return ASTERISCO; }
"/"		    { return BARRA; }
"<"		    { return MENOR; }
"<="		  { return MENORIGUAL; }
">"		    { return MAIOR; }
">="		  { return MAIORIGUAL; }
"=="		  { return IGUALIGUAL; }
"!="		  { return DIFERENTE; }
"="		    { return IGUAL; }
";"		    { return PONTOVIRGULA; }
","		    { return VIRGULA; }
"("		    { return ABREPARENTESES; }
")"		    { return FECHAPARENTESES; }
"["		    { return ABRECOLCHETE; }
"]"		    { return FECHACOLCHETE; }
"{"		    { return ABRECHAVE; }
"}"		    { return FECHACHAVE; }
{ID}		  { yylval.str = strdup(yytext); return ID; }
{NUM}		  { yylval.digito = atoi(yytext); return DIGITO; }
{STR}     { yylval.str = strdup(yytext); return CADEIASTRING; }

{IDINVALIDO}+ printf("ERRO! ID inválido: %s\n", yytext);
{INVALIDO}

%%

