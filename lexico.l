%{
  #include <stdio.h>
int level;
%}

%option noyywrap
PALAVRASCHAVE else|if|int|return|void|while|string
OPERADORES \+|\-|\*|\/|\<|<=|\>|>=|==|!=|\=|\;|\,|[()]|[[]]|[{}]    
ID [a-zA-Z]+
IDINVALIDO [0-9]+[a-zA-Z]+[0-9]*|[0-9]*[a-zA-Z]+[0-9]+
NUM [0-9][0-9]*
STR ["][^"]*[^\n]["]   
INVALIDO (.)

%x COMENT

%%
\r|\n|\t
"/*"  			BEGIN( COMENT ); level = 1; printf( "Início do comentário:\n");

<COMENT>{ 
"/*"			{level++; printf( "/*");}
"*/"			{if(--level == 0){ BEGIN( INITIAL ); printf( "\nFim do comentário!\n");} else{  printf( "*/"); }}
\n			{ECHO;} 
}

{PALAVRASCHAVE} printf("Palavra-chave: %s\n", yytext );
{OPERADORES} printf( "Operador: %s\n", yytext );
{IDINVALIDO}+ printf("ERRO! ID inválido: %s\n", yytext);
{ID} printf("ID: %s\n", yytext );
{NUM}+ printf("NUM: %s\n", yytext );
{STR} printf( "String: %s\n", yytext );
{INVALIDO}
%%

int main(void)
{
yylex();
return 0;
}
