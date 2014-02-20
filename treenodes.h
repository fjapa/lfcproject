#ifndef TREENODES_H
#define TREENODES_H

/*
NÓS DA ÁRVORE ABSTRATA DA ANÁLISE SINTÁTICA.
*/


typedef struct PROG *tProgram; /*programa*/
typedef struct DECLIST *tDecList; /*declaração-lista*/
typedef struct DEC *tDec; /*declaração*/
typedef struct VARDEC *tVarDec; /*var-declaração*/
typedef struct TIPOESP *tTipoEsp; /*tipo-especificador*/
typedef struct FUNDEC *tFunDec; /*fun-declaração*/
typedef struct PARAMS *tParams; /*params*/
typedef struct PARAMLIST *tParamList; /*param-lista*/
typedef struct VAR *tVar; /*var*/
typedef struct ARGLIST *tArgList; /*arg-lista*/
typedef struct ARGS *tArgs; /*args*/
typedef struct EXP *tExp; /*expressão*/
typedef struct VAZIO *tVazio; /*vazio*/
typedef struct ATIV *tAtiv; /*ativação*/

typedef char *string;


/* (01) programa —> declaração-lista*/
struct PROG {
    tDecList declaracaoLista;
};
tProgram producao_programa_declaracaolista(tDecList declaracaoLista); /* programa —> declaração-lista */

/* (02) declaração-lista —> declaração-lista declaração | declaração*/
struct DECLIST{
    enum {producao_decList, producao_declaracao} tipoDeProducao;
    union{
        struct{
            tDecList declaracaoLista;
            tDec declaracao;
        } Tvariasdeclaracoes;
        tDec declaracao;
    } uniao;
};
tDecList producao_declist_declaracaolista(tDecList declaracaoLista, tDec declaracao); /* declaracoes -> declaracoes declaracao */
tDecList producao_declist_declaracao(tDec declaracao); /* declaracoes -> declaracao */

/*(03) declaração —> var-declaração | fun-declaração*/
struct DEC {
    enum{producao_varDec,producao_funDec}tipoDeProducao;
    union{
        tVarDec varDeclaracao;
        tFunDec funDeclaracao;
    } uniao;
};
tDec producao_varDec(tVarDec varDeclaracao );
tDec producao_funDec(tDec funDeclaracao );

/*(04) var-declaração —» tipo-especificador ID ; | tipo-especificador ID [ NUM ] ;*/
struct VARDEC{
   enum{producao_tipoEspecificador_ID_pontoevirgula,producao_tipoespecificador_ID_NUM}tipoDeProducao;
   union{
       struct{
           tTipoEsp tipoEspecificador;
           char* id;
       }Tvariasdeclaracoes;
       struct{
           tTipoEsp tipoEspecificador;
           char* id;  /* falta o '[]' q n sei como declara*/
           int num;
       };
   };
};


/*(05) tipo-especificador -> int | void*/
struct TIPOESP{
    enum{producao_int,producao_void}tipoDeProducao;
    union{
        tTipoEsp tipoEspecificador;
        string 'void';
    };
};


/*(07) params -> param-lista|void */
struct PARAMS {
    enum{producao_void, producao_paramlist} tipoDeProducao;
    union{
        string 'void';
        tParamList paramList;
    } uniao;
};

tParams producao_params_void(string 'void'); /* params -> param-lista */
tParams producao_params_paramLista(tParamList paramList); /* params -> void */

/*(19) var -> ID|ID[expressão] */
struct VAR {
    enum{producao_id, producao_exp} tipoDeProducao;
    union{
        string id;
        tExp exp;
    } uniao;
};
tVar producao_var_id(string id); /* var -> ID */
tVar producao_var_id_aC_expressao_fC(tExp exp); /* var -> ID[expressão] | aC ->Abre colchete, fC ->Fecha colchete */

/*(27) ativação —> ID ( args ) */
struct ATIV {
	tArgs args;
};
tArgs producao_ativacao_ID_aP_args_fP(tArgs args); /* ativação —> ID ( args )  */

/*(28) args -> arg-lista | vazio */
struct ARGS {
    enum{producao_argList, producao_vazio} tipoDeProducao;
    union{
        tArgList argLista;
        tVazio vazio;
    } uniao;
};
tArgs producao_args_vazio(); /* args -> vazio */
tArgs producao_args_argLista(tArgList argLista); /* args -> arg-lista */

/*(29) arg-lista -> arg-lista,expressão | expressão */
struct ARGLIST{
        enum {producao_argList, producao_exp} tipodeproducao;
        union{
            struct{
                tArgList argLista;
                tExp exp;
            } Tvariasdeclaracoes;
            tExp exp;
        } uniao;
};
tArgList producao_arglista_argList_vir_expressao(tArgList argLista, tExp exp); // arg-lista -> arg-lista,expressão | vir -> vírgula
tArgList producao_arglista_expressao(tDec declaracao); // arg-lista -> expressão 
#endif

/*
(01) programa —> declaração-lista
(02) declaração-lista —> declaração-lista declaração | declaração
(03) declaração —> var-declaração | fun-declaração
(04) var-declaração —» tipo-especificador ID ; | tipo-especificador ID [ NUM ] ;
(05) tipo-especificador -> int | void
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
(19) var —> ID | I D [ expressão ]
(20) simples-expressão —> soma-expressão relacional soma-expressão | soma-expressão
(21) relacional -> <= | < | > | >= | » | !=
(22) soma-expressão —> soma-expressão soma termo | termo
(23) soma —> + | -
(24) termo —> termo multfator | fator
(25) mult -> * | /
(26) fator -> ( expressão ) | var | ativação | NUM
(27) ativação —> ID ( args )
(28) args —> arg-lista | vazio
(29) arg-lista -> arg-lista, expressão | expressão
*/
