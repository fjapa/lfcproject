#ifndef TREENODES_H
#define TREENODES_H

/*
NÓS DA ÁRVORE ABSTRATA DA ANÁLISE SINTÁTICA.
*/


typedef struct PROG *tProgram; /*programa*/
typedef struct DECLIST *tDeclist; /*declaração-lista*/
typedef struct DEC *tDec; /*declaração*/
typedef struct VARDEC *tDec; /*var-declaração*/
typedef struct TIPOESP *tTipoesp; /*tipo-especificador*/
typedef struct FUNDEC *tFundec; /*fun-declaração*/
typedef struct PARAMS * tParams /*params*/
typedef struct VAR *tVar; /*var*/
typedef struct ARGLIST * tArgList /*arg-lista*/
typedef struct ARGS * tArgs /*args*/
typedef struct EXP * tExp /*expressão*/
typedef struct VAZIO *tVazio /*vazio*/

typedef char *string;


/* (1) programa —> declaração-lista*/
struct PROG {
tDeclist declaracao-lista;
};


/* (2) declaração-lista —> declaração-lista declaração | declaração*/
struct DECLIST{
        enum {producao_declist, producao_declaracao} tipodeproducao;
        union{	struct{
tDeclist declaracaoLista;
tDec declaracao;
} Tvariasdeclaracoes;

tDec declaracao;

} uniao;
};


/*(7) params -> param-lista|void */
struct PARAMS {
enum{producao_void, producao_paramLista} tipoDeProducao;

union{
string 'void';
tParams params;
} uniao;
};
tParams producao_params_void(string void);
tParams producao_params_paramLista(tParams params);

/*(19) var -> ID|ID[expressão] */
struct VAR {
enum{producao_id, producao_expressao} tipoDeProducao;

union{
string id;
tVar var;
} uniao;
};
tVar producao_params_id(string id);
tVar producao_params_id_aC_exp_fC(tVar params); /*aC ->Abre colchete | fC ->Fecha colchete*/

/*(28) args -> arg-lista | vazio */
struct ARGS {
enum{producao_argLista, producao_vazio} tipoDeProducao;

union{	tArgLista argLista;
tVazio vazio;
} uniao;
};
tArgs producao_args_vazio();
tArgs producao_args_argLista(tArgs args);

/*(29) arg-lista -> arg-lista,expressão | expressão */
struct ARGLIST{
        enum {producao_arg-lista, producao_expressao} tipodeproducao;
        union{	struct{
tArgList argLista;
tExp expressao;
} Tvariasdeclaracoes;

tExp expressao;

} uniao;
};

#endif

/*
programa —> declaração-lista
declaração-lista —> declaração-lista declaração | declaração
declaração —> var-declaração | fun-declaração
var-declaração —» tipo-especificador ID ; | tipo-especificador ID [ NUM ] ;
tipo-especificador -> int | void
fun-declaração —> tipo-especificador ID ( params ) composto-decl
params —> param-lista | void
param-lista —> param-lista, param | param
param —> tipo-especificador ID | tipo-especificador ID []
composto-decl —> { local-declarações statement-lista
local-declarações -> local-declarações var-declaração | vazio
statement-lista —> statement-lista statement | vazio
statement —> expressão-decl | composto-decl | seleção-decl | iteração-decl | retorno-decl
expressão-decl -> expressão ; | ;
seleção-decl —> if ( expressão ) statement | if ( expressão ) statement else statement
iteração-decl —> while ( expressão ) statement
retorno-decl —> return ; | return expressão ;
expressão -> var = expressão | simples-expressão
var —> ID | I D [ expressão ]
simples-expressão —> soma-expressão relacional soma-expressão | soma-expressão
relacional -> <= | < | > | >= | » | !=
soma-expressão —> soma-expressão soma termo | termo
soma —> + | -
termo —> termo multfator | fator
mult -> * | /
fator -> ( expressão ) | var | ativação | NUM
ativação —> ID ( args )
args —> arg-lista | vazio
arg-lista -> arg-lista, expressão | expressão
*/
