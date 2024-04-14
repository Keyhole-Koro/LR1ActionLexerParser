#include "main.h"

int main() {
    char *path = "/workspaces/LR1_parser/syntaxSamples/sample1.txt";
    
    processSyntaxTxt(path);

    showProductionRules();
    
    return 0;
}