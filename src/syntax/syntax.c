#include "syntax.h"

#define terminal 1
#define non_terminal 0

int current_num_syntax = 0;
int max_size_syntax = 32;
ProductionRule *prod_rules;

static ProductionRule *constructRule(symbol left, symbol *right);
static void registerSyntax(symbol left, symbol *right);

void processSyntaxTxt(char *file_path) {
    FILE *file;
    char line[50];

    symbol left = 0;
    symbol *right;
    char *rest = NULL;

    file = fopen(file_path, "r");
    if (file == NULL) {
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        readUntil(isSpace, line, &rest); // just for consumming
        if (*rest == '\n') left = 0;
        
        if (left == 0) {
            printf("11\n");
            left = mapString(readUntil(isColon, line, &rest), non_terminal);
            printf("12\n");
            right = processRightBuffer(readUntil(isEnd, rest, &rest));
            printf("13\n");
        } else {
            readUntil(isPipe, line, &rest); // just for consumming
            char *right_buffer = readUntil(isEnd, rest, &rest);
            right = processRightBuffer(right_buffer);
        }
        printf("9\n");
        registerSyntax(left, right);
    }

    fclose(file);
}

static ProductionRule *constructRule(symbol left, symbol *right) {
    ProductionRule *rule = malloc(sizeof(ProductionRule));
    rule->nonTerminal = left;
    rule->production = right;
    return rule;
}

static void registerSyntax(symbol left, symbol *right) {
    
    ProductionRule *newRule = constructRule(left, right);

    if (current_num_syntax > max_size_syntax) prod_rules = (ProductionRule *)realloc(
        prod_rules, max_size_syntax * 2 * sizeof(ProductionRule));

    prod_rules[max_size_syntax++] = *newRule;
}

symbol *processRightBuffer(char *buffer) {
    int initial_buffer_size = 10;

    symbol *initial_sym_buffer = (symbol *)malloc(initial_buffer_size * sizeof(symbol));
    if (initial_sym_buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    symbol *sym_buffer = initial_sym_buffer;
    int num_sym = 0;
    char *rest;
    while (*buffer) {
        if (num_sym >= initial_buffer_size) {
            initial_buffer_size *= 2;
            symbol *new_sym_buffer = (symbol *)realloc(initial_sym_buffer, initial_buffer_size * sizeof(symbol));
            if (new_sym_buffer == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                exit(EXIT_FAILURE);
            }
            sym_buffer = new_sym_buffer;
        }

        if (*buffer == ' ') {
            buffer++;
            continue;
        }

        if (*buffer == '\'') {
            sym_buffer[num_sym++] = mapString(readUntil(isSingleQuote, buffer, &rest), terminal);
            buffer = rest;
            continue;
        }
        
        sym_buffer[num_sym++] = mapString(readUntil(isSpace, buffer, &rest), non_terminal);
        buffer = rest;

        buffer++;
    }

    return sym_buffer;
}

void showProductionRules() {
    for (int i = 0; i < max_size_syntax; i++) {
        ProductionRule *rule = &prod_rules[i];
        printf("----\n");
        printf("nonTerminal: %d\n", rule->nonTerminal);
        printf("production:");
        for (int i = 0; i < rule->num_symbol; i++) {
            printf(" %d", rule->production[i]);
        }
        printf("\n");
        printf("----\n");
    }
}