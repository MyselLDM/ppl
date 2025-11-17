#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_INIT_SIZE 16

#include <stddef.h>

#include "../global/dictionary.h"

typedef struct {
  size_t line;
  size_t offset;
  const char* lexeme;
  TokenType token_type;
  TokenSpecial token_type_special;
} Token;

typedef struct {
  Token* token;
  size_t length;
  size_t capacity;
} Tokens;

Tokens token_create();
void token_push(Tokens* tokens, char* lexeme, TokenType token_type,
                TokenSpecial token_type_special, size_t line, size_t offset);
#endif