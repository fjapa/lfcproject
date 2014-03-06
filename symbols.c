#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "symbols.h"

#define SIZE 127

/*
FUNÇÕES SYMBOLS.
*/

/*Função para criar os símbolos*/
tSymbol newSymbol(string name, tSymbol nextSym) {
    tSymbol sym = malloc(sizeof (*sym));
    sym->name = name;
    sym->nextSymbol = nextSym;
    return sym;
}

/*Função Hash para armazenamento dos símbolos*/
unsigned int hash(char *chave) {
    unsigned int h = 0;
    char *s;
    for (s = chave; *s; s++)
        h = h * 65599 + *s;
    return h;
}

/*Tabela de strings*/
static tSymbol stringTable[SIZE];


/*Função para pegar o símbolo na StringTable a partir do identificador. */
tSymbol getSymbol(string name) {
    int index = hash(name) % SIZE;
    tSymbol s = stringTable[index];
    tSymbol sym;
    for (sym = s; sym; sym = sym->nextSymbol)
        if (strcmp(sym->name, name) == 0)
            return sym;
    sym = newSymbol(name, s);
    stringTable[index] = sym;
    return sym;
}

/*Função para retornar o identificador do símbolo*/
string getName(tSymbol sym) {
    return sym->name; //Retorna o identificador.
}

/*Função para desalocar o símbolo da memória*/
void freeSymbol(tSymbol sym) {
    while (sym != NULL) {
        free(sym->name); //Desaloca o identificador do símbolo.
        tSymbol temp = sym; //Cria um símbolo temporário para auxiliar.
        sym = sym->nextSymbol; //O símbolo passa a ser seu sucessor.
        free(temp); //O símbolo temporário é destruído.
    }

}

/*Função para limpar a tabela, ou seja, remover os símbolos existentes nela.*/
void freeTable() {
    int aux;
    for (aux = 0; aux < SIZE; aux++) {
        freeSymbol(stringTable[aux]);
        stringTable[aux] = NULL;
    }
}

