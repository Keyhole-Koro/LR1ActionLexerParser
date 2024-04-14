#ifndef SYNTAX_H
#define SYNTAX_H

#include "expr.h"
#include "token.h"

typedef struct {
    char *nonTerminal;
    char *production;
} ProductionRule;

ProductionRule *productions;

void processSyntaxTxt(char *file_path);

void registerSyntax(char *);

#endif