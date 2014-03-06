#ifndef SYMBOLS_H
#define SYMBOLS_H

#include "util.h"

/*
ESTRUTURA SYMBOLS.
*/

typedef struct Symbol *tSymbol;

struct Symbol {
    string name;
    tSymbol nextSymbol;
};

tSymbol getSymbol(string name);
string getName(tSymbol sym);
void freeSymbol(tSymbol sym);
void freeTable();

#endif
