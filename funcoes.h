#include <stdlib.h>
#include "treenodes.h"

/*
FUNÇÕES GERADORAS DA ÁRVORE ABSTRATA DE ANÁLISE SINTÁTICA.
 */

/*(01) programa —> declaração-lista*/
tProgram producao_programa_declaracaoLista(tDecList declLista) {
    tProgram prog = malloc(sizeof (*prog));
    prog->declaracaoLista = declLista;
    return prog;
}

/*(02) declaração-lista —> declaração-lista declaração | declaração*/
tDecList producao_declaracaoLista_declaracaoLista_declaracao(tDecList declLista, tDec d) {
    tDecList declaracaoLista = malloc(sizeof (*declaracaoLista));
    declaracaoLista->uniao.tVariasDeclaracoes.declaracaoLista = declLista;
    declaracaoLista->uniao.tVariasDeclaracoes.declaracao = d;
    return declaracaoLista;
}

tDecList producao_declaracaoLista_decl(tDec d) {
    tDecList declaracaoLista = malloc(sizeof (*declaracaoLista));
    declaracaoLista->uniao.declaracao = d;
    return declaracaoLista;
}

/*(03) declaração —> var-declaração | fun-declaração*/
tDec producao_declaracao_varDeclaracao(tVarDec varDecl) {
    tDec declaracao = malloc(sizeof (*declaracao));
    declaracao->uniao.varDeclaracao = varDecl;
    return declaracao;
}

tDec producao_declaracao_funDeclaracao(tFunDec funDecl) {
    tDec declaracao = malloc(sizeof (*declaracao));
    declaracao->uniao.funDeclaracao = funDecl;
    return declaracao;
}

/*(04) var-declaração —» tipo-especificador ID ; | tipo-especificador ID [ NUM ] ;*/
tVarDec producao_vardeclaracao_tipoEspecificador_id(tTipoEsp tipoEspec, string id) {
    tVarDec varDeclaracao = malloc(sizeof (*varDeclaracao));
    varDeclaracao->uniao.tVariasDeclaracoes.tipoEspecificador = tipoEspec;
    varDeclaracao->uniao.tVariasDeclaracoes.id = id;
    return varDeclaracao;
}

tVarDec producao_vardeclaracao_tipoEspecificador_id_aC_NUM_fC(tTipoEsp tipoEspec, string id, int num) {
    tVarDec varDeclaracao = malloc(sizeof (*varDeclaracao));
    varDeclaracao->uniao.tVariasDeclaracoes2.tipoEspecificador = tipoEspec;
    varDeclaracao->uniao.tVariasDeclaracoes2.id = id;
    varDeclaracao->uniao.tVariasDeclaracoes2.num = num;
    return varDeclaracao;
}

/*(05) tipo-especificador -> int | void*/ /*String adicionada à linguagem C-*/
tTipoEsp producao_tipoEspecificador_int() {
    tTipoEsp tipoEspecificador = malloc(sizeof (*tipoEspecificador));
    return tipoEspecificador;
}

tTipoEsp producao_tipoEspecificador_void() {
    tTipoEsp tipoEspecificador = malloc(sizeof (*tipoEspecificador));
    return tipoEspecificador;
}

tTipoEsp producao_tipoEspecificador_string() {
    tTipoEsp tipoEspecificador = malloc(sizeof (*tipoEspecificador));
    return tipoEspecificador;
}

/*(06) fun-declaração —> tipo-especificador ID ( params ) composto-decl*/
tFunDec producao_tipoEspecificador_ID_aP_params_fP_compostoDecl(tTipoEsp tipoEspec, string id, tParams params, tCompDec compostoDecl) {
    tFunDec funDeclaracao = malloc(sizeof (*funDeclaracao));
    funDeclaracao->tipoEsp = tipoEspec;
    funDeclaracao->ID = id;
    funDeclaracao->params = params;
    funDeclaracao->compDec = compostoDecl;
    return funDeclaracao;
}

/*(07) params -> param-lista|void */
tParams producao_params_paramLista(tParamList paramLista) {
    tParams params = malloc(sizeof (*params));
    params->uniao.paramList = paramLista;
    return params;
}

tParams producao_params_void() {
    tParams params = malloc(sizeof (*params));
    return params;
}

/*(08) param-lista —> param-lista, param | param*/
tParamList producao_paramLista_paramLista_virg_param(tParamList paramLista, tParam p) {
    tParamList param_Lista = malloc(sizeof (*param_Lista));
    param_Lista->uniao.tVariasDeclaracoes.paramList = paramLista;
    param_Lista->uniao.tVariasDeclaracoes.param = p;
    return param_Lista;
}

tParamList producao_paramLista_param(tParam p) {
    tParamList param_Lista = malloc(sizeof (*param_Lista));
    param_Lista->uniao.param = p;
    return param_Lista;
}

/*(09) param —> tipo-especificador ID | tipo-especificador ID []*/
tParam producao_param_tipoEspecificador_ID(tTipoEsp tipoEspec, string id) {
    tParam param = malloc(sizeof (*param));
    param->uniao.tVariasDeclaracoes.tipoEsp = tipoEspec;
    param->uniao.tVariasDeclaracoes.id = id;
    return param;
}

tParam producao_param_tipoEspecificador_ID_aC_fC(tTipoEsp tipoEspec, string id) {
    tParam param = malloc(sizeof (*param));
    param->uniao.tVariasDeclaracoes2.tipoEsp = tipoEspec;
    param->uniao.tVariasDeclaracoes2.id = id;
    return param;
}

/*(10) composto-decl —> { local-declarações statement-lista }*/
tCompDec producao_aCh_localDeclaracao_statmentLista_fCh(tLocalDec localDecl, tStatList statementLista) {
    tCompDec compostoDecl = malloc(sizeof (*compostoDecl));
    compostoDecl->localDec = localDecl;
    compostoDecl->statList = statementLista;
    return compostoDecl;
}

/*(11) local-declarações -> local-declarações var-declaração | vazio */
tLocalDec producao_localDeclaracao_localDeclaracao_varDeclaracao(tLocalDec localDecl, tVarDec varDecl) {
    tLocalDec localDeclaracoes = malloc(sizeof (*localDeclaracoes));
    localDeclaracoes->uniao.tVariasDeclaracoes.localDec = localDecl;
    localDeclaracoes->uniao.tVariasDeclaracoes.varDec = varDecl;
    return localDeclaracoes;
}

tLocalDec producao_localDeclaracao_vazio() {
    tLocalDec localDeclaracoes = malloc(sizeof (*localDeclaracoes));
    return localDeclaracoes;
}

/*(12) statement-lista —> statement-lista statement | vazio */
tStatList producao_statementLista_statementLista_statement(tStatList stmLista, tStat stm) {
    tStatList statement_Lista = malloc(sizeof (*statement_Lista));
    statement_Lista->uniao.tVariasDeclaracoes.statList = stmLista;
    statement_Lista->uniao.tVariasDeclaracoes.statement = stm;
    return statement_Lista;
}

tStatList producao_statementLista_vazio() {
    tStatList statement_Lista = malloc(sizeof (*statement_Lista));
    return statement_Lista;
}

/*(13) statement —> expressão-decl | composto-decl | seleção-decl | iteração-decl | retorno-decl*/
tStat producao_statement_expressaoDecl(tExpDec expressaoDecl) {
    tStat statement = malloc(sizeof (*statement));
    statement->uniao.expDec = expressaoDecl;
    return statement;
}

tStat producao_statement_compostoDecl(tCompDec compostoDecl) {
    tStat statement = malloc(sizeof (*statement));
    statement->uniao.compDec = compostoDecl;
    return statement;
}

tStat producao_statement_selecaoDecl(tSelDec selecaoDecl) {
    tStat statement = malloc(sizeof (*statement));
    statement->uniao.selDec = selecaoDecl;
    return statement;
}

tStat producao_statement_iteracaoDecl(tIterDec interacaoDecl) {
    tStat statement = malloc(sizeof (*statement));
    statement->uniao.iterDec = interacaoDecl;
    return statement;
}

tStat producao_statement_retornoDecl(tRetDec retornoDecl) {
    tStat statement = malloc(sizeof (*statement));
    statement->uniao.retDec = retornoDecl;
    return statement;
}

/*(14) expressão-decl -> expressão ; | ; */
tExpDec producao_expressaoDecl_expressao_pontoVirgula(tExp expressao) {
    tExpDec expressaoDecl = malloc(sizeof (*expressaoDecl));
    expressaoDecl->uniao.tVariasDeclaracoes.exp = expressao;
    return expressaoDecl;
}

tExpDec producao_expressaoDecl_pontoVirgula() {
    tExpDec expressaoDecl = malloc(sizeof (*expressaoDecl));
    return expressaoDecl;
}

/*(15) seleção-decl —> if ( expressão ) statement | if ( expressão ) statement else statement*/
tSelDec producao_selecaoDecl_if_aP_exp_fP_statement(tExp expressao, tStat stm) {
    tSelDec selecaoDecl = malloc(sizeof (*selecaoDecl));
    selecaoDecl->uniao.tVariasDeclaracoes.exp = expressao;
    selecaoDecl->uniao.tVariasDeclaracoes.statement = stm;
    return selecaoDecl;
}

tSelDec producao_selecaoDecl_if_aP_exp_fP_statement_else_statement(tExp expressao, tStat stm_if, tStat stm_else) {
    tSelDec selecaoDecl = malloc(sizeof (*selecaoDecl));
    selecaoDecl->uniao.tVariasDeclaracoes2.exp = expressao;
    selecaoDecl->uniao.tVariasDeclaracoes2.statementIf = stm_if;
    selecaoDecl->uniao.tVariasDeclaracoes2.statementElse = stm_else;
    return selecaoDecl;
}

/*(16) iteração-decl —> while ( expressão ) statement */
tIterDec producao_itDec_while_aP_expressao_fP_statement(tExp expressao, tStat stm) {
    tIterDec interacaoDecl = malloc(sizeof (*interacaoDecl));
    interacaoDecl->exp = expressao;
    interacaoDecl->statement = stm;
    return interacaoDecl;
}

/*(17) retorno-decl —> return ; | return expressão ; */
tRetDec producao_retornoDecl_return_pontoVirgula() {
    tRetDec retornoDecl = malloc(sizeof (*retornoDecl));
    return retornoDecl;
}

tRetDec producao_retornoDecl_return_expressao(tExp expressao) {
    tRetDec retornoDecl = malloc(sizeof (*retornoDecl));
    retornoDecl->uniao.tVariasDeclaracoes.exp = expressao;
    return retornoDecl;
}

/*(18) expressão -> var = expressão | simples-expressão */
tExp producao_expressao_var_igual_expressao(tVar var, tExp expressao) {
    tExp expr = malloc(sizeof (*expr));
    expr->uniao.tVariasDeclaracoes.var = var;
    expr->uniao.tVariasDeclaracoes.expressao = expressao;
    return expr;
}

tExp producao_expressao_simplesExpressao(tSimExp simplesExpressao) {
    tExp expr = malloc(sizeof (*expr));
    expr->uniao.simplesExp = simplesExpressao;
    return expr;
}

/*(19) var -> ID|ID[expressão] */
tVar producao_var_id(string id) {
    tVar var = malloc(sizeof (*var));
    var->uniao.id = id;
    return var;
}

tVar producao_var_id_aC_exp_fC(string id, tExp expressao) {
    tVar var = malloc(sizeof (*var));
    var->uniao.tVariasDeclaracoes.id = id;
    var->uniao.tVariasDeclaracoes.expressao = expressao;
    return var;
}

/*(20) simples-expressão —> soma-expressão relacional soma-expressão | soma-expressão */
tSimExp producao_simplesExpressao_somaExpressao_relacional_somaExpressao(tSomaExp somaExpr1, tRelacional rel, tSomaExp somaExpr2) {
    tSimExp simplesExpressao = malloc(sizeof (*simplesExpressao));
    simplesExpressao->uniao.tVariasDeclaracoes.somaExp1 = somaExpr1;
    simplesExpressao->uniao.tVariasDeclaracoes.relacional = rel;
    simplesExpressao->uniao.tVariasDeclaracoes.somaExp2 = somaExpr2;
    return simplesExpressao;
}

tSimExp producao_simplesExpressao_somaExpressao(tSomaExp somaExp) {
    tSimExp simplesExpressao = malloc(sizeof (*simplesExpressao));
    simplesExpressao->uniao.somaExp = somaExp;
    return simplesExpressao;
}

/*(21) relacional -> <= | < | > | >= | == | != */
tRelacional producao_relacional_menorIgual() {
    tRelacional rel = malloc(sizeof (*rel));
    return rel;
}

tRelacional producao_relacional_menor() {
    tRelacional rel = malloc(sizeof (*rel));
    return rel;
}

tRelacional producao_relacional_maior() {
    tRelacional rel = malloc(sizeof (*rel));
    return rel;
}

tRelacional producao_relacional_maiorIgual() {
    tRelacional rel = malloc(sizeof (*rel));
    return rel;
}

tRelacional producao_relacional_igualIgual() {
    tRelacional rel = malloc(sizeof (*rel));
    return rel;
}

tRelacional producao_relacional_diferente() {
    tRelacional rel = malloc(sizeof (*rel));
    return rel;
}

/*(22) soma-expressão —> soma-expressão soma termo | termo */
tSomaExp producao_somaExpressao_somaExpressao_soma_termo(tSomaExp sumExp, tSoma soma, tTermo termo) {
    tSomaExp somaExpressao = malloc(sizeof (*somaExpressao));
    somaExpressao->uniao.tVariasDeclaracoes.somaExp = sumExp;
    somaExpressao->uniao.tVariasDeclaracoes.soma = soma;
    somaExpressao->uniao.tVariasDeclaracoes.termo = termo;
    return somaExpressao;
}

tSomaExp producao_somaExpressao_termo(tTermo t) {
    tSomaExp somaExpressao = malloc(sizeof (*somaExpressao));
    somaExpressao->uniao.termo = t;
    return somaExpressao;
}

/*(23) soma —> + | - */
tSoma producao_soma_mais() {
    tSoma soma = malloc(sizeof (*soma));
    return soma;
}

tSoma producao_soma_menos() {
    tSoma soma = malloc(sizeof (*soma));
    return soma;
}

/*(24) termo —> termo mult fator | fator */
tTermo producao_termo_termo_mult_fator(tTermo termo, tMult mult, tFator fator) {
    tTermo t = malloc(sizeof (*t));
    t->uniao.tVariasDeclaracoes.termo = termo;
    t->uniao.tVariasDeclaracoes.mult = mult;
    t->uniao.tVariasDeclaracoes.fator = fator;
    return t;
}

tTermo producao_termo_fator(tFator f) {
    tTermo t = malloc(sizeof (*t));
    t->uniao.fator = f;
    return t;
}

/*(25) mult -> * | / */
tMult producao_mult_asterisco() {
    tMult mult = malloc(sizeof (*mult));
    return mult;
}

tMult producao_mult_aBarra() {
    tMult mult = malloc(sizeof (*mult));
    return mult;
}

/*(26) fator -> ( expressão ) | var | ativação | NUM | cadeia-string */ //String adicionada à linguagem C-
tFator producao_fator_aP_exp_fP(tExp expressao) {
    tFator fator = malloc(sizeof (*fator));
    fator->uniao.expressao = expressao;
    return fator;
}

tFator producao_fator_var(tVar var) {
    tFator fator = malloc(sizeof (*fator));
    fator->uniao.var = var;
    return fator;
}

tFator producao_fator_ativacao(tAtiv ativ) {
    tFator fator = malloc(sizeof (*fator));
    fator->uniao.ativacao = ativ;
    return fator;
}

tFator producao_fator_num(int num) {
    tFator fator = malloc(sizeof (*fator));
    fator->uniao.NUM = num;
    return fator;
}

tFator producao_fator_cadeiaString(string str) {
    tFator fator = malloc(sizeof (*fator));
    fator->uniao.cadeiaString = str;
    return fator;
}

/*(27) ativação —> ID ( args ) */
tAtiv producao_ativacao_ID_aP_args_fP(string id, tArgs argumentos) {
    tAtiv ativacao = malloc(sizeof (*ativacao));
    ativacao->id = id;
    ativacao->args = argumentos;
    return ativacao;
}

/*(28) args -> arg-lista | vazio */
tArgs producao_args_argLista(tArgList argumentosList) {
    tArgs args = malloc(sizeof (*args));
    args->uniao.argList = argumentosList;
    return args;
}

tArgs producao_args_vazio() {
    tArgs args = malloc(sizeof (*args));
    return args;
}

/*(29) arg-lista -> arg-lista,expressão | expressão */
tArgList producao_argLista_argLista_virgula_expressao(tArgList listaArgumentos, tExp expressao) {
    tArgList argLista = malloc(sizeof (*argLista));
    argLista->uniao.tVariasDeclaracoes.argList = listaArgumentos;
    argLista->uniao.tVariasDeclaracoes.exp = expressao;
    return argLista;
}

tArgList producao_argLista_expressao(tExp expr) {
    tArgList argLista = malloc(sizeof (*argLista));
    argLista->uniao.exp = expr;
    return argLista;
}

/*(30) VAZIO -> £ */
tVazio producao_vazio_vazio() {
    tVazio vazio = malloc(sizeof (*vazio));
    return vazio;
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
