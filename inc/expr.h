#ifndef EXPR_H
#define EXPR_H

typedef struct {
    Token left;
    Token *right;
} Expr;

#endif  