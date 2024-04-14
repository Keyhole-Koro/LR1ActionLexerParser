#include "stringMapper.h"

int nonTerminal_number = -1;
int terminal_number = 1;

int current_num_strmap = 0;
int max_size_strmap = 32;
StringMapping *mappings_terminal;
StringMapping *mappings_nonTerminal;

StringMapping *string_mappings;

static StringMapping *registerStringMapping(char *str);
static StringMapping *findStringMapping(char *str);
StringMapping *constructStringMapping(char *str);

symbol mapString(char *str, bool isTerminal) {
    if (isTerminal) string_mappings = mappings_terminal;
    else string_mappings = mappings_nonTerminal;
    
    for (int i = 0; i < current_num_strmap; i++) {
        if (string_mappings[i].string != NULL && strcmp(str, string_mappings[i].string) == 0) {
            return string_mappings[i].number;
        }
    }

    StringMapping *found_mapping = findStringMapping(str);

    if (found_mapping != NULL) return found_mapping->number;
    
    StringMapping *new_mapping = registerStringMapping(str);
    return new_mapping->number;
}

static StringMapping *registerStringMapping(char *str) {
    StringMapping *new_mapping = (StringMapping *)malloc(sizeof(StringMapping));
    if (new_mapping == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_mapping->string = strdup(str);
    if (new_mapping->string == NULL) {
        free(new_mapping);
        fprintf(stderr, "String duplication failed\n");
        exit(EXIT_FAILURE);
    }

    new_mapping->number = current_num_strmap++;
    new_mapping->next = NULL;

    if (string_mappings == NULL) {
        string_mappings = new_mapping;
    } else {
        StringMapping *current = string_mappings;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_mapping;
    }

    return new_mapping;
}

static StringMapping *findStringMapping(char *str) {
    StringMapping *current = string_mappings;
    while (current != NULL) {
        if (strcmp(current->string, str) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

StringMapping *constructStringMapping(char *str) {
    StringMapping *new_mapping = (StringMapping *)malloc(sizeof(StringMapping));
    if (new_mapping == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    new_mapping->string = strdup(str);
    if (new_mapping->string == NULL) {
        free(new_mapping);
        fprintf(stderr, "String duplication failed\n");
        exit(EXIT_FAILURE);
    }

    new_mapping->number = current_num_strmap++;
    new_mapping->next = NULL;
    return new_mapping;
}
