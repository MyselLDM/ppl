#include "token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../global/debug_print.h"

Tokens token_create() {
  Tokens tokens;
  tokens.length = 0;
  tokens.capacity = TOKEN_INIT_SIZE;
  tokens.token = malloc(TOKEN_INIT_SIZE * sizeof(Token));
  DEBUG_PRINT("tokens struct created");
  return tokens;
}

void token_push(Tokens* tokens, char* lexeme, char* token_type,
                const char* token_type_special, size_t line, size_t offset) {
  if (tokens->length == tokens->capacity) {
    tokens->capacity *= 2;
    tokens->token = realloc(tokens->token, tokens->capacity * sizeof(Token));
    DEBUG_PRINT("tokens struct resized from %d to %d\n", tokens->capacity / 2,
                tokens->capacity);
  }
  tokens->token[tokens->length++] =
      (Token){line, offset, lexeme, token_type, token_type_special};
  DEBUG_PRINT("{%s, %s, %s} at line %d offset %d token pushed\n", lexeme,
              token_type, token_type_special, line, offset);
}
