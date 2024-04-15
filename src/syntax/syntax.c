#include "syntax.h"

#define terminal 1
#define non_terminal 0

int current_num_syntax = 0;
int max_size_syntax = 32;
ProductionRule *prod_rules;

static ProductionRule *constructRule(symbol left, symbol *right, int size_right);
static void registerSyntax(symbol left, symbol *right, int size_right);

void processSyntaxTxt(char *file_path) {
    FILE *file;
    char line[50];

    file = fopen(file_path, "r");
    if (file == NULL) {
        exit(EXIT_FAILURE);
    }

    Token head;
    head.next = NULL;
    Token *cur = &head;

    while (fgets(line, sizeof(line), file) != NULL) {
        cur = tokenizeLine(line, cur);
    }

    symbol left = 0;
    int size_right = 0;
    symbol *right;
    char *rest = NULL;

    for (Token *current = &head; current; current = current->next) {
        
        
    }

    fclose(file);
}

static ProductionRule *constructRule(symbol left, symbol *right, int size_right) {
    ProductionRule *rule = (ProductionRule *)malloc(sizeof(ProductionRule));
    if (rule == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    rule->nonTerminal = left;
    rule->num_symbol = size_right;
    rule->production = right;
    rule->next = NULL;
    return rule;
}

static void registerSyntax(symbol left, symbol *right, int size_right) {
    ProductionRule *newRule = constructRule(left, right, size_right);
    if (prod_rules == NULL) {
        prod_rules = newRule;
    } else {
        ProductionRule *current = prod_rules;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newRule;
    }
}

int processRightBuffer(char *buffer, symbol **right) {
    int initial_buffer_size = 10;
    symbol *sym_buffer = (symbol *)malloc(initial_buffer_size * sizeof(symbol));
    if (sym_buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    int num_sym = 0;
    char *rest;
    while (*buffer) {
        if (num_sym >= initial_buffer_size) {
            initial_buffer_size *= 2;
            symbol *new_sym_buffer = (symbol *)realloc(sym_buffer, initial_buffer_size * sizeof(symbol));
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
    *right = sym_buffer;

    return num_sym;
}

void showProductionRules() {
    ProductionRule *current = prod_rules;
    while (current != NULL) {
        printf("----\n");
        printf("nonTerminal: %d\n", current->nonTerminal);
        printf("number of productions: %d\n", current->num_symbol);
        printf("production:");
        for (int i = 0; i < current->num_symbol; i++) {
            printf(" %d", current->production[i]);
        }
        printf("\n");
        printf("----\n");
        current = current->next;
    }
}
