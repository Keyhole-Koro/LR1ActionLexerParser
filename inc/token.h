#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    NUMBER,

    ADD,      // +
    SUB,      // -
    MUL,      // *
    DIV,      // /

    L_PARENTHESES, // (
    R_PARENTHESES, // )

} TokenKind;

typedef struct {
  TokenKind tk;
  char *val;
} Token;

#endif