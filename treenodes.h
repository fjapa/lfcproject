#ifndef TREENODES_H
#define TREENODES_H

/*
NÓS DA ÁRVORE ABSTRATA DE ANÁLISE SINTÁTICA.
 */

typedef struct PROG *tProgram; /*programa*/
typedef struct DECLIST *tDecList; /*declaração-lista*/
typedef struct DEC *tDec; /*declaração*/
typedef struct VARDEC *tVarDec; /*var-declaração*/
typedef struct TIPOESP *tTipoEsp; /*tipo-especificador*/
typedef struct FUNDEC *tFunDec; /*fun-declaração*/
typedef struct PARAMS * tParams; /*params*/
typedef struct PARAM * tParam; /*param*/
typedef struct PARAMLIST *tParamList; /*param-lista*/
typedef struct VAR *tVar; /*var*/
typedef struct ARGLIST * tArgList; /*arg-lista*/
typedef struct ARGS * tArgs; /*args*/
typedef struct EXP * tExp; /*expressão*/
typedef struct VAZIO *tVazio; /*vazio*/
typedef struct ATIV *tAtiv; /*ativação*/
typedef struct FATOR *tFator; /*fator*/
typedef struct MULT * tMult; /*mult*/
typedef struct TERMO * tTermo; /*termo*/
typedef struct SOMA * tSoma; /*soma*/
typedef struct SOMAEXP *tSomaExp; /*soma-expressão*/
typedef struct RELACIONAL *tRelacional; /*relacional*/
typedef struct SIMEXP *tSimExp; /*simples-expressão*/
typedef struct RETDEC *tRetDec; /*retorno-decl*/
typedef struct ITERDEC *tIterDec; /*iteração-decl*/
typedef struct STAT *tStat; /*statement*/
typedef struct EXPDEC *tExpDec; /*expressão-decl*/
typedef struct COMPDEC *tCompDec; /*composto-decl*/
typedef struct SELDEC *tSelDec; /*seleção-decl*/
typedef struct LOCALDEC *tLocalDec; /*local-decl*/
typedef struct STATLIST *tStatList; /*statement-lista*/

typedef char *string;

/*(01) programa —> declaração-lista*/
struct PROG {
    tDecList declaracaoLista;
};
tProgram producao_programa_declaracaoLista(tDecList declaracaoLista); /* programa —> declaração-lista */

/*(02) declaração-lista —> declaração-lista declaração | declaração*/
struct DECLIST {

    enum {
        producao_decList, producao_declaracao
    } tipoDeProducao;

    union {

        struct {
            tDecList declaracaoLista;
            tDec declaracao;
        } tVariasDeclaracoes;
        tDec declaracao;
    } uniao;
};
tDecList producao_declaracaoLista_declaracaoLista_declaracao(tDecList declaracaoLista, tDec declaracao); /* declaracoes -> declaracoes declaracao */
tDecList producao_declaracaoLista_decl(tDec declaracao); /* declaracoes -> declaracao */

/*(03) declaração —> var-declaração | fun-declaração*/
struct DEC {

    enum {
        producao_varDec, producao_funDec
    } tipoDeProducao;

    union {
        tVarDec varDeclaracao;
        tFunDec funDeclaracao;
    } uniao;
};
tDec producao_declaracao_varDeclaracao(tVarDec varDeclaracao);
tDec producao_declaracao_funDeclaracao(tFunDec funDeclaracao);

/*(04) var-declaração —» tipo-especificador ID ; | tipo-especificador ID [ NUM ] ;*/
struct VARDEC {

    enum {
        producao_tipoEspecificador_ID_pontoevirgula, producao_tipoespecificador_ID_aC_NUM_fC
    } tipoDeProducao;

    union {

        struct {
            tTipoEsp tipoEspecificador;
            string id;
        } tVariasDeclaracoes;

        struct {
            tTipoEsp tipoEspecificador;
            string id;
            int num;
        } tVariasDeclaracoes2;
    } uniao;
};
tVarDec producao_vardeclaracao_tipoEspecificador_id(tTipoEsp tipoEspecificador, string id);
tVarDec producao_vardeclaracao_tipoEspecificador_id_aC_NUM_fC(tTipoEsp tipoEspecificador, string id, int num);

/*(05) tipo-especificador -> int | void | string*/
struct TIPOESP {

    enum {
        producao_int, producao_void
    } tipoDeProducao;

    union {

        struct {
        } tInT;

        struct {
        } tVoid;

        struct {
        } tString;
    } uniao;
};
tTipoEsp producao_tipoEspecificador_int();
tTipoEsp producao_tipoEspecificador_void();
tTipoEsp producao_tipoEspecificador_string();

/*(06) fun-declaração —> tipo-especificador ID ( params ) composto-decl*/
struct FUNDEC {
    tTipoEsp tipoEsp;
    string ID;
    tParams params;
    tCompDec compDec;
};
tFunDec producao_tipoEspecificador_ID_aP_params_fP_compostoDecl(tTipoEsp tipoEsp, string ID, tParams params, tCompDec compDec);

/*(07) params -> param-lista|void */
struct PARAMS {

    enum {
        producao_void1, producao_paramlist
    } tipoDeProducao;

    union {

        struct {
        } tVoid;
        tParamList paramList;
    } uniao;
};
tParams producao_params_paramLista(tParamList paramList); /* params -> param-lista */
tParams producao_params_void(); /* params -> void */

/*(08) param-lista —> param-lista, param | param*/
struct PARAMLIST {

    enum {
        producao_paramList_virg_param, producao_param
    } tipoDeProducao;

    union {

        struct {
            tParamList paramList;
            tParam param;
        } tVariasDeclaracoes;
        tParam param;
    } uniao;
};
tParamList producao_paramLista_paramLista_virg_param(tParamList paramList, tParam param);
tParamList producao_paramLista_param(tParam param);

/*(09) param —> tipo-especificador ID | tipo-especificador ID []*/
struct PARAM {

    enum {
        producao_tipoEsp_ID, producao_tipoEsp_ID_aC_fC
    } tipoDeProducao;

    union {

        struct {
            tTipoEsp tipoEsp;
            string id;
        } tVariasDeclaracoes;

        struct {
            tTipoEsp tipoEsp;
            string id;
        } tVariasDeclaracoes2;
    } uniao;
};
tParam producao_param_tipoEspecificador_ID(tTipoEsp tipoEsp, string id);
tParam producao_param_tipoEspecificador_ID_aC_fC(tTipoEsp tipoEsp, string id);

/*(10) composto-decl —> { local-declarações statement-lista }*/
struct COMPDEC {
    tLocalDec localDec;
    tStatList statList;
};
tCompDec producao_aCh_localDeclaracao_statmentLista_fCh(tLocalDec localDec, tStatList statList);

/*(11) local-declarações -> local-declarações var-declaração | vazio */
struct LOCALDEC {

    enum {
        producao_localDeclacracoes_varDeclaracao, producao_vazio
    } tipoDeProducao;

    union {

        struct {
            tLocalDec localDec;
            tVarDec varDec;
        } tVariasDeclaracoes;
        tVazio vazio;
    } uniao;
};
tLocalDec producao_localDeclaracao_localDeclaracao_varDeclaracao(tLocalDec localDec, tVarDec varDec);
tLocalDec producao_localDeclaracao_vazio();

/*(12) statement-lista —> statement-lista statement | vazio */

struct STATLIST {

    enum {
        producao_statement_lista, producao_statement
    } tipoDeProducao;

    union {

        struct {
            tStatList statList;
            tStat statement;
        } tVariasDeclaracoes;
        tVazio vazio;
    } uniao;
};
tStatList producao_statementLista_statementLista_statement(tStatList statList, tStat statement);
tStatList producao_statementLista_vazio();

/*(13) statement —> expressão-decl | composto-decl | seleção-decl | iteração-decl | retorno-decl*/
struct STAT {

    enum {
        producao_expressaoDecl, producao_compostoDecl, producao_selecaoDecl, producao_iteracaoDecl, producao_retornoDecl
    } tipoDeProducao;

    union {
        tExpDec expDec;
        tCompDec compDec;
        tSelDec selDec;
        tIterDec iterDec;
        tRetDec retDec;
    } uniao;
};
tStat producao_statement_expressaoDecl(tExpDec expressaodecl);
tStat producao_statement_compostoDecl(tCompDec compDec);
tStat producao_statement_selecaoDecl(tSelDec selDec);
tStat producao_statement_iteracaoDecl(tIterDec iterDec);
tStat producao_statement_retornoDecl(tRetDec retDec);

/*(14) expressão-decl -> expressão ; | ; */
struct EXPDEC {

    enum {
        producao_exp_pontoVirgula, producao_pontoVirgula
    } tipoDeProducao;

    union {

        struct {
            tExp exp;
        } tVariasDeclaracoes;

        struct {
        } tVariasDeclaracoes2;
    } uniao;
};
tExpDec producao_expressaoDecl_expressao_pontoVirgula(tExp exp); /* expressão-decl -> expressão ; */
tExpDec producao_expressaoDecl_pontoVirgula(); /* expressão-decl -> ; */

/*(15) seleção-decl —> if ( expressão ) statement | if ( expressão ) statement else statement*/
struct SELDEC {

    enum {
        producao_if_aP_expressao_fP_statement, producao_if_aP_expressao_fP_statement_else_statement
    } tipoDeProducao;

    union {

        struct {
            tExp exp;
            tStat statement;
        } tVariasDeclaracoes;

        struct {
            tExp exp;
            tStat statementIf;
            tStat statementElse;
        } tVariasDeclaracoes2;
    } uniao;
};
tSelDec producao_selecaoDecl_if_aP_exp_fP_statement(tExp Exp, tStat stat); /* seleção-decl —> if ( expressão ) statement */
tSelDec producao_selecaoDecl_if_aP_exp_fP_statement_else_statement(tExp Exp, tStat statIf, tStat statElse); /* seleção-decl —> if ( expressão ) statement else statement */

/*(16) iteração-decl —> while ( expressão ) statement */
struct ITERDEC {
    tExp exp;
    tStat statement;
};
tIterDec producao_itDec_while_aP_expressao_fP_statement(tExp Exp, tStat stat); /* iteração-decl —> while ( expressão ) statement */

/*(17) retorno-decl —> return ; | return expressão ; */
struct RETDEC {

    enum {
        producao_pontoVirgula1, producao_expressao
    } tipoDeProducao;

    union {

        struct {
        } tVoid;

        struct {
            tExp exp;
        } tVariasDeclaracoes;
    } uniao;
};
tRetDec producao_retornoDecl_return_pontoVirgula(); /* retorno-decl -> return ; */
tRetDec producao_retornoDecl_return_expressao(tExp exp); /* retorno-decl -> return expressão */

/*(18) expressão -> var = expressão | simples-expressão */
struct EXP {

    enum {
        producao_varIgualExpressao, producao_simplesExpressao
    } tipoDeProducao;

    union {

        struct {
            tVar var;
            tExp expressao;
        } tVariasDeclaracoes;
        tSimExp simplesExp;
    } uniao;
};
tExp producao_expressao_var_igual_expressao(tVar var, tExp expressao); /* expressao -> var = expressao */
tExp producao_expressao_simplesExpressao(tSimExp simplesExp); /* expressao -> simples-expressão */

/*(19) var -> ID|ID[expressão] */
struct VAR {

    enum {
        producao_id, producao_ID_aC_exp_fC
    } tipoDeProducao;

    union {
        string id;

        struct {
            string id;
            tExp expressao;
        } tVariasDeclaracoes;
    } uniao;
};
tVar producao_var_id(string id); /* var -> ID */
tVar producao_var_id_aC_exp_fC(string id, tExp exp); /* var -> ID[expressão] | aC ->Abre colchete, fC ->Fecha colchete */

/*(20) simples-expressão —> soma-expressão relacional soma-expressão | soma-expressão */
struct SIMEXP {

    enum {
        producao_somaexpressao_relacional_somaexpressao
    } tipoDeProducao; //Nesse caso, surge uma dúvida. Duas produções iguais.

    union {

        struct {
            tSomaExp somaExp1;
            tRelacional relacional;
            tSomaExp somaExp2;
        } tVariasDeclaracoes;
        tSomaExp somaExp;
    } uniao;
};
tSimExp producao_simplesExpressao_somaExpressao_relacional_somaExpressao(tSomaExp somaExp1, tRelacional relacional, tSomaExp somaExp2); /* simples-expressão —> soma-expressão relacional soma-expressão */
tSimExp producao_simplesExpressao_somaExpressao(tSomaExp somaExp); /* simples-expressão —> soma-expressão */

/*(21) relacional -> <= | < | > | >= | == | != */
struct RELACIONAL {

    enum {
        producao_menorIgual, producao_menor, producao_maior, producao_maiorIgual, producao_igualIgual, producao_diferente
    } tipoDeProducao;

    union {

        struct {
        } menorIgual;

        struct {
        } menor;

        struct {
        } maior;

        struct {
        } maiorIgual;

        struct {
        } igualIgual;

        struct {
        } diferente;
    } uniao;
};
tRelacional producao_relacional_menorIgual(); /* relacional -> <= */
tRelacional producao_relacional_menor(); /* relacional -> < */
tRelacional producao_relacional_maior(); /* relacional -> > */
tRelacional producao_relacional_maiorIgual(); /* relacional -> >= */
tRelacional producao_relacional_igualIgual(); /* relacional -> = */
tRelacional producao_relacional_diferente(); /* relacional -> != */

/*(22) soma-expressão —> soma-expressão soma termo | termo */
struct SOMAEXP {

    enum {
        producao_somaexpressao, producao_soma, producao_termo
    } tipoDeProducao;

    union {

        struct {
            tSomaExp somaExp;
            tSoma soma;
            tTermo termo;
        } tVariasDeclaracoes;
        tTermo termo;
    } uniao;
};
tSomaExp producao_somaExpressao_somaExpressao_soma_termo(tSomaExp somaExp, tSoma soma, tTermo termo); /* soma-expressão —> soma-expressão soma termo */
tSomaExp producao_somaExpressao_termo(tTermo termo); /* soma-expressão —> termo */

/*(23) soma —> + | - */
struct SOMA {

    enum {
        producao_mais, producao_menos
    } tipoDeProducao;

    union {

        struct {
        } mais;

        struct {
        } menos;
    } uniao;
};
tSoma producao_soma_mais(); /* soma -> + */
tSoma producao_soma_menos(); /* soma -> - */

/*(24) termo —> termo mult fator | fator */
struct TERMO {

    enum {
        producao_termo_mult_fator, producao_fator
    } tipoDeProducao;

    union {

        struct {
            tTermo termo;
            tMult mult;
            tFator fator;
        } tVariasDeclaracoes;
        tFator fator;
    } uniao;
};
tTermo producao_termo_termo_mult_fator(tTermo termo, tMult mult, tFator fator); /* termo -> termo multfator */
tTermo producao_termo_fator(tFator fator); /* termo -> fator */

/*(25) mult -> * | / */
struct MULT {

    enum {
        producao_asterisco, producao_aBarra
    } tipoDeProducao;

    union {

        struct {
        } asterisco;

        struct {
        } aBarra;
    } uniao;
};
tMult producao_mult_asterisco(); /* mult -> * */
tMult producao_mult_aBarra(); /* mult -> / */

/*(26) fator -> ( expressão ) | var | ativação | NUM | cadeia-string */ //String adicionada à linguagem C-
struct FATOR {

    enum {
        producao_aP_expressao_fP, producao_var, producao_ativacao, producao_num
    } tipoDeProducao;

    union {
        tExp expressao;
        tVar var;
        tAtiv ativacao;
        int NUM;
        string cadeiaString;
    } uniao;
};
tFator producao_fator_aP_exp_fP(tExp expressao); /* fator -> ( expressão ) */
tFator producao_fator_var(tVar avar); /* fator -> var */
tFator producao_fator_ativacao(tAtiv ativacao); /* fator -> ativação */
tFator producao_fator_num(int num); /* fator -> NUM */
tFator producao_fator_cadeiaString(string str); /* fator -> cadeia-string */

/*(27) ativação —> ID ( args ) */
struct ATIV {
    string id;
    tArgs args;
};
tAtiv producao_ativacao_ID_aP_args_fP(string id, tArgs args); /* ativação —> ID ( args ) */

/*(28) args -> arg-lista | vazio */
struct ARGS {

    enum {
        producao_argList, producao_vazio2
    } tipoDeProducao;

    union {
        tArgList argList;
        tVazio vazio;
    } uniao;
};
tArgs producao_args_argLista(tArgList argLista); /* args -> arg-lista */
tArgs producao_args_vazio(); /* args -> vazio */

/*(29) arg-lista -> arg-lista,expressão | expressão */
struct ARGLIST {

    enum {
        producao_argList1, producao_exp
    } tipoDeProducao;

    union {

        struct {
            tArgList argList;
            tExp exp;
        } tVariasDeclaracoes;
        tExp exp;
    } uniao;
};
tArgList producao_argLista_argLista_virgula_expressao(tArgList argLista, tExp exp); // arg-lista -> arg-lista,expressão | vir -> vírgula
tArgList producao_argLista_expressao(tExp exp); // arg-lista -> expressão

/*(30) VAZIO -> £ */
struct VAZIO {
};
tVazio producao_vazio_vazio();

#endif

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
(10) composto-decl —> { local-declarações statement-lista }
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
 */
