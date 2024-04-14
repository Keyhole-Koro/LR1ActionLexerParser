#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    SYMBOL,

    ADD,      // +
    SUB,   1   // -
    MUL,      // *
    DIV,      // /

    L_PARENTHESES, // (
    R_PARENTHESES, // )

} TokenType;

typedef struct {
  TokenType type;
  char *val;
} Token;

typedef int symbol;

struct KeyValue {
  char *str;
  symbol sym;
};

extern struct KeyValue single_char[];

TokenType correspondingToken(char *substring, size_t substring_length, struct KeyValue *symbols);


#endif