#ifndef TREENODES_H
#define TREENODES_H

/*
	NÓS DA ÁRVORE ABSTRATA DA ANÁLISE SINTÁTICA.
*/


typedef struct S *SS;
typedef struct params * tParams
typedef struct var *tVar;

typedef char *string;


/*(7) params -> param-lista|void	*/
struct params {
	enum{producao_void, producao_paramLista} tipoDeProducao;
	
	union{
	
		string 'void';
		
		tParams params;
		
	} uniao;
};
tParams producao_params_void(string void);
tParams producao_params_paramLista(tParams params);

/*(19) var -> ID|ID[expressão]	*/
struct var {
	enum{producao_id, producao_expressao} tipoDeProducao;
	
	union{
	
		string id;
		
		tVar var;
		
	} uniao;
};
tVar producao_params_id(string id);
tVar producao_params_id_aC_exp_fC(tVar params); /*aC ->Abre colchete | fC ->Fecha colchete*/

/*(EXEMPLO) S -> (S)|a	*/
struct S {
	
	enum{producao_a, producao_s} tipoDeProducao;
	
	union{
	
		string a;
		
		SS s;
		
	} uniao;
};

SS producao_S_a(string a);
SS producao_S_abpr_S_fcpar(SS s);


#endif
