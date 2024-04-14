#ifndef SYNTAX_H
#define SYNTAX_H

#include <stdio.h>

#include "symbol.h"
#include "stringMapper.h"
#include "utils.h"

typedef struct {
    symbol nonTerminal;
    int num_symbol;
    symbol *production;
} ProductionRule;

ProductionRule *productions;

void processSyntaxTxt(char *file_path);

void showProductionRules();

symbol *processRightBuffer(char *buffer);

#endif
