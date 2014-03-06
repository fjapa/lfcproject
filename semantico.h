#include "util.h"
#include "treenodes.h"

/*
ESTRUTURA DO BINDING.
*/

typedef struct BINDING *tBinding;

//(01) Binding do tipo: simples, vetor ou função
struct BINDING {

    enum {
        bindingSimples, bindingVetor, bindingFuncao
    } tipoDeProducao;

    union {
        tTipoEsp tipoEsp;

        struct {
            tTipoEsp tipoEsp;
            int tamanho;
        } tVetor;

        struct {
            tTipoEsp tipoEsp;
            tBinding argumento;
        } tFuncao;
    } uniao;

};

tBinding producao_binding_simples(tTipoEsp tipoEsp);
tBinding producao_binding_vetor(tTipoEsp tipoEsp, int tamanho);
tBinding producao_binding_funcao(tTipoEsp tipoEsp, tBinding argumento);
