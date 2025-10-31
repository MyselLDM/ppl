#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_INIT_SIZE 16

#include <stddef.h>

typedef struct {
  size_t line;
  const char* lexeme;
  const char* token_type;
  const char* token_type_special;
} Token;

typedef struct {
  Token* token;
  size_t length;
  size_t capacity;
} Tokens;

Tokens token_create();
void token_push(Tokens* tokens, char* lexeme, char* token_type,
                char* token_type_special, size_t line);

#endif