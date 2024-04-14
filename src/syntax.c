#include "syntax.h"

void tokenize(char *file_path) {
    FILE *file;
    char line[50];

    char *left;
    char *right;

    file = fopen(file_path, "r");
    if (file == NULL) {
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        if (!isspace(*line)) left = NULL;
        
        if (left == NULL) {
            left = readUntil(isColon, line);
            right = readUntil(isEnd, line);
        }
        
    }

    fclose(file);
}

void registerSyntax(char *syntax) {

}