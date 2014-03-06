%{
#include "semantico.c"
#include "treenodes.h"
#include "treenodes.c"
#include "util.h"

tProgram prog;

/*
ANALISADOR SINTÁTICO.
*/

%}

%expect 1

%union{
    char* str;
    int digito;
    tProgram programa;
    tDecList declaracaoLista;
    tDec declaracao;
    tVarDec varDeclaracao;
    tTipoEsp tipoEspecificador;
    tFunDec funDeclaracao;
    tParams params;
    tParamList paramLista;
    tParam param;
    tCompDec compostoDecl;
    tLocalDec localDeclaracoes;
    tStatList statementLista;
    tStat statement;
    tExpDec expressaoDecl;
    tSelDec selecaoDecl;
    tIterDec iteracaoDecl;
    tRetDec retornoDecl;
    tExp expressao;
    tVar var;
    tSimExp simplesExpressao;
    tRelacional relacional;
    tSomaExp somaExpressao;
    tSoma soma;
    tTermo termo;
    tMult mult;
    tFator fator;
    tAtiv ativacao;
    tArgs args;
    tArgList argLista;
};

%token STRING IF ELSE INT RETURN VOID WHILE
%token MAIS MENOS ASTERISCO BARRA MENOR MENORIGUAL MAIOR MAIORIGUAL IGUALIGUAL
%token DIFERENTE IGUAL PONTOVIRGULA VIRGULA ABREPARENTESES FECHAPARENTESES
%token ABRECOLCHETE FECHACOLCHETE ABRECHAVE FECHACHAVE
%token<str> ID
%token<str> CADEIASTRING
%token<digito> DIGITO

%type <programa>            PROGRAMA
%type <declaracaoLista>     DECLARACAO_LISTA
%type <declaracao>          DECLARACAO
%type <varDeclaracao>       VAR_DECLARACAO
%type <tipoEspecificador>   TIPO_ESPECIFICADOR
%type <funDeclaracao>       FUN_DECLARACAO
%type <params>              PARAMS
%type <paramLista>          PARAM_LISTA
%type <param>               PARAM
%type <compostoDecl>        COMPOSTO_DECL
%type <localDeclaracoes>    LOCAL_DECLARACOES
%type <statementLista>      STATEMENT_LISTA
%type <statement>           STATEMENT
%type <expressaoDecl>       EXPRESSAO_DECL
%type <selecaoDecl>         SELECAO_DECL
%type <iteracaoDecl>        INTERACAO_DECL
%type <retornoDecl>         RETORNO_DECL
%type <expressao>           EXPRESSAO
%type <var>                 VAR
%type <simplesExpressao>    SIMPLES_EXPRESSAO
%type <relacional>          RELACIONAL
%type <somaExpressao>       SOMA_EXPRESSAO
%type <soma>                SOMA
%type <termo>               TERMO
%type <mult>                MULT
%type <fator>               FATOR
%type <ativacao>            ATIVACAO
%type <args>                ARGS
%type <argLista>            ARG_LISTA

%start PROGRAMA

%%
/*(01) programa —> declaração-lista*/
PROGRAMA: 
 DECLARACAO_LISTA{prog = producao_programa_declaracaoLista($1); $$ = prog;}
;

/*(02) declaração-lista —> declaração-lista declaração | declaração*/
DECLARACAO_LISTA:
 DECLARACAO_LISTA DECLARACAO{$$ = producao_declaracaoLista_declaracaoLista_declaracao($1, $2);}|
 DECLARACAO{$$ = producao_declaracaoLista_decl($1);}
;

/*(03) declaração —> var-declaração | fun-declaração*/
DECLARACAO:
 VAR_DECLARACAO{$$ = producao_declaracao_varDeclaracao($1);}|
 FUN_DECLARACAO{$$ = producao_declaracao_funDeclaracao($1);}
;

/*(04) var-declaração —» tipo-especificador ID ; | tipo-especificador ID [ NUM ] ;*/
VAR_DECLARACAO:
 TIPO_ESPECIFICADOR ID PONTOVIRGULA{$$ = producao_vardeclaracao_tipoEspecificador_id($1, getSymbol($2));}|
 TIPO_ESPECIFICADOR ID ABRECOLCHETE DIGITO FECHACOLCHETE PONTOVIRGULA{$$ = producao_vardeclaracao_tipoEspecificador_id_aC_NUM_fC($1, getSymbol($2), $4);}
;

/*(05) tipo-especificador -> int | void*/ //String adicionada à linguagem C-
TIPO_ESPECIFICADOR:
 INT{$$ = tInt;}|
 VOID{$$ = tVoid;}|
 STRING{$$ = tString;}
;

/*(06) fun-declaração —> tipo-especificador ID ( params ) composto-decl*/
FUN_DECLARACAO:
 TIPO_ESPECIFICADOR ID ABREPARENTESES PARAMS FECHAPARENTESES COMPOSTO_DECL{$$ = producao_tipoEspecificador_ID_aP_params_fP_compostoDecl($1, getSymbol($2), $4, $6);}
;

/*(07) params -> param-lista|void */
PARAMS:
 PARAM_LISTA{$$ = producao_params_paramLista($1);}|
 VOID{$$ = producao_params_void();}
;

/*(08) param-lista —> param-lista, param | param*/
PARAM_LISTA:
 PARAM_LISTA VIRGULA PARAM{$$ = producao_paramLista_paramLista_virg_param($1, $3);}|
 PARAM{$$ = producao_paramLista_param($1);}
;

/*(09) param —> tipo-especificador ID | tipo-especificador ID []*/
PARAM:
 TIPO_ESPECIFICADOR ID{$$ = producao_param_tipoEspecificador_ID($1, getSymbol($2));}|
 TIPO_ESPECIFICADOR ID ABRECOLCHETE FECHACOLCHETE{$$ = producao_param_tipoEspecificador_ID_aC_fC($1, getSymbol($2));}
;

/*(10) composto-decl —> { local-declarações statement-lista }*/
COMPOSTO_DECL:
 ABRECHAVE LOCAL_DECLARACOES STATEMENT_LISTA FECHACHAVE{$$ = producao_aCh_localDeclaracao_statmentLista_fCh($2, $3);}
;

/*(11) local-declarações -> local-declarações var-declaração | vazio */
LOCAL_DECLARACOES:
 LOCAL_DECLARACOES VAR_DECLARACAO{$$ = producao_localDeclaracao_localDeclaracao_varDeclaracao($1, $2);}|
 { $$ = producao_localDeclaracao_vazio(); }
;

/*(12) statement-lista —> statement-lista statement | vazio */
STATEMENT_LISTA:
 STATEMENT_LISTA STATEMENT{$$ = producao_statementLista_statementLista_statement($1, $2);}|
 { $$ = producao_statementLista_vazio(); }
;

/*(13) statement —> expressão-decl | composto-decl | seleção-decl | iteração-decl | retorno-decl*/
STATEMENT:
 EXPRESSAO_DECL{$$ = producao_statement_expressaoDecl($1);}|
 COMPOSTO_DECL{$$ = producao_statement_compostoDecl($1);}|
 SELECAO_DECL{$$ = producao_statement_selecaoDecl($1);}|
 INTERACAO_DECL{$$ = producao_statement_iteracaoDecl($1);}|
 RETORNO_DECL{$$ = producao_statement_retornoDecl($1);}
;

/*(14) expressão-decl -> expressão ; | ; */
EXPRESSAO_DECL:
 EXPRESSAO PONTOVIRGULA{$$ = producao_expressaoDecl_expressao_pontoVirgula($1);}|
 PONTOVIRGULA{$$ = producao_expressaoDecl_pontoVirgula();}
;

/*(15) seleção-decl —> if ( expressão ) statement | if ( expressão ) statement else statement*/
SELECAO_DECL:
 IF ABREPARENTESES EXPRESSAO FECHAPARENTESES STATEMENT{$$ = producao_selecaoDecl_if_aP_exp_fP_statement($3, $5);}|
 IF ABREPARENTESES EXPRESSAO FECHAPARENTESES STATEMENT ELSE STATEMENT{$$ = producao_selecaoDecl_if_aP_exp_fP_statement_else_statement($3, $5, $7);}
;

/*(16) iteração-decl —> while ( expressão ) statement */
INTERACAO_DECL:
 WHILE ABREPARENTESES EXPRESSAO FECHAPARENTESES STATEMENT{$$ = producao_itDec_while_aP_expressao_fP_statement($3, $5);}
;

/*(17) retorno-decl —> return ; | return expressão ; */
RETORNO_DECL:
 RETURN PONTOVIRGULA{$$ = producao_retornoDecl_return_pontoVirgula();}|
 RETURN EXPRESSAO PONTOVIRGULA{$$ = producao_retornoDecl_return_expressao($2);}
;

/*(18) expressão -> var = expressão | simples-expressão */
EXPRESSAO:
 VAR IGUAL EXPRESSAO{$$ = producao_expressao_var_igual_expressao($1, $3);}|
 SIMPLES_EXPRESSAO{$$ = producao_expressao_simplesExpressao($1);}
;

/*(19) var -> ID|ID[expressão] */
VAR:
 ID{$$ = producao_var_id(getSymbol($1));}|
 ID ABRECOLCHETE EXPRESSAO FECHACOLCHETE{$$ = producao_var_id_aC_exp_fC(getSymbol($1), $3);}
;

/*(20) simples-expressão —> soma-expressão relacional soma-expressão | soma-expressão */
SIMPLES_EXPRESSAO:
 SOMA_EXPRESSAO RELACIONAL SOMA_EXPRESSAO{$$ = producao_simplesExpressao_somaExpressao_relacional_somaExpressao($1, $2, $3);}|
 SOMA_EXPRESSAO{$$ = producao_simplesExpressao_somaExpressao($1);}
;

/*(21) relacional -> <= | < | > | >= | == | != */
RELACIONAL:
 MENORIGUAL{$$ = tMenorIgual;}|
 MENOR{$$ = tMenor;}|
 MAIOR{$$ = tMaior;}|
 MAIORIGUAL{$$ = tMaiorIgual;}|
 IGUALIGUAL{$$ = tIgualIgual;}|
 DIFERENTE{$$ = tDiferente;}
;

/*(22) soma-expressão —> soma-expressão soma termo | termo */
SOMA_EXPRESSAO:
 SOMA_EXPRESSAO SOMA TERMO{$$ = producao_somaExpressao_somaExpressao_soma_termo($1, $2, $3);}|
 TERMO{$$ = producao_somaExpressao_termo($1);}
;

/*(23) soma —> + | - */
SOMA:
 MAIS{$$ = tMais;}|
 MENOS{$$ = tMenos;}
;

/*(24) termo —> termo mult fator | fator */
TERMO:
 TERMO MULT FATOR{$$ = producao_termo_termo_mult_fator($1, $2, $3);}|
 FATOR{$$ = producao_termo_fator($1);}
;

/*(25) mult -> * | / */
MULT:
 ASTERISCO{$$ = tAsterisco;}|
 BARRA{$$ = tABarra;}
;

/*(26) fator -> ( expressão ) | var | ativação | NUM | cadeia-string */ //String adicionada à linguagem C-
FATOR:
ABREPARENTESES EXPRESSAO FECHAPARENTESES{$$ = producao_fator_aP_exp_fP($2);}|
 VAR{$$ = producao_fator_var($1);}|
 ATIVACAO{$$ = producao_fator_ativacao($1);}|
 DIGITO{$$ = producao_fator_num($1);}|
 CADEIASTRING{$$ = producao_fator_cadeiaString($1);}
;

/*(27) ativação —> ID ( args ) */
ATIVACAO:
 ID ABREPARENTESES ARGS FECHAPARENTESES{$$ = producao_ativacao_ID_aP_args_fP(getSymbol($1), $3);}
;

/*(28) args -> arg-lista | vazio */
ARGS:
 ARG_LISTA{$$ = producao_args_argLista($1);}|
 { $$ = producao_args_vazio(); }
;

/*(29) arg-lista -> arg-lista,expressão | expressão */
ARG_LISTA:
 ARG_LISTA VIRGULA EXPRESSAO{$$ = producao_argLista_argLista_virgula_expressao($1, $3);}|
 EXPRESSAO{$$ = producao_argLista_expressao($1);}
%%

#include <stdlib.h>
#include <stdio.h>

yyerror(char *s) {
    printf("ERRO SINTÁTICO!\n");
    exit(1);
}

main() {
    yyparse();
    return 0;
}

/*
GRAMÁTICA EM BNF PARA C-

(01) programa —> declaração-lista
(02) declaração-lista —> declaração-lista declaração | declaração
(03) declaração —> var-declaração | fun-declaração
(04) var-declaração —» tipo-especificador ID ; | tipo-especificador ID [ NUM ] ;
(05) tipo-especificador -> int | void | string
(06) fun-declaração —> tipo-especificador ID ( params ) composto-decl
(07) params —> param-lista | void
(08) param-lista —> param-lista, param | param
(09) param —> tipo-especificador ID | tipo-especificador ID []
(10) composto-decl —> { local-declarações statement-lista
(11) local-declarações -> local-declarações var-declaração | vazio
(12) statement-lista —> statement-lista statement | vazio
(13) statement —> expressão-decl | composto-decl | seleção-decl | iteração-decl | retorno-decl
(14) expressão-decl -> expressão ; | ;
(15) seleção-decl —> if ( expressão ) statement | if ( expressão ) statement else statement
(16) iteração-decl —> while ( expressão ) statement
(17) retorno-decl —> return ; | return expressão ;
(18) expressão -> var = expressão | simples-expressão
(19) var —> ID | ID [ expressão ]
(20) simples-expressão —> soma-expressão relacional soma-expressão | soma-expressão
(21) relacional -> <= | < | > | >= | == | !=
(22) soma-expressão —> soma-expressão soma termo | termo
(23) soma —> + | -
(24) termo —> termo mult fator | fator
(25) mult -> * | /
(26) fator -> ( expressão ) | var | ativação | NUM | cadeia-string
(27) ativação —> ID ( args )
(28) args —> arg-lista | vazio
(29) arg-lista -> arg-lista, expressão | expressão

//--------------------------------------------------------------------------------------------//

COMANDOS:

  bison -v -d -o sintatico.c sintatico.y

  flex -v -t lexico.l > lexico.c

  gcc sintatico.c lexico.c -o compilador

 */
