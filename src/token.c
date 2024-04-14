#include "token.h"

struct KeyValue single_char[] = {
  {"+", ADD},
  {"-", SUB},
  {"*", MUL},
  {"/", DIV},
};

/** @brief find the corresponding Token from keyvalue declared in token.h **/
TokenType correspondingToken(char *substring, size_t substring_length, struct KeyValue *symbols) {
  size_t size = ARRAY_LENGTH(symbols);
  for (int i = 0; i < size; i++) {
    char *key = symbols[i].Key;
    if (ifMatch(substring, key, substring_length)) {
        return symbols[i].Value;
    }
  }
  return -1;
}