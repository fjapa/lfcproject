#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbols.c"
#include "treenodes.h"
#include "util.h"
#include "semantico.h"

/*
FUNÇÕES DO BINDING.
*/

//(01) Binding do tipo: simples, vetor ou função
tBinding producao_binding_simples(tTipoEsp t){
	tBinding binding = malloc(sizeof(*binding));
	binding->tipoDeProducao = bindingSimples;
	binding->uniao.tipoEsp = t; 
	return binding;
}

tBinding producao_binding_vetor(tTipoEsp t, int tam){
	tBinding binding = malloc(sizeof(*binding));
	binding->tipoDeProducao = bindingVetor;
	binding->uniao.tVetor.tipoEsp = t; 
	binding->uniao.tVetor.tamanho = tam;
	return binding;
}

tBinding producao_binding_funcao(tTipoEsp t, tBinding arg){
	tBinding binding = malloc(sizeof(*binding));
	binding->tipoDeProducao = bindingFuncao;
	binding->uniao.tFuncao.tipoEsp = t; 
	binding->uniao.tFuncao.argumento = arg;
	return binding;
}

