#include "token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Tokens token_create() {
  Tokens tokens;
  tokens.length = 0;
  tokens.capacity = TOKEN_INIT_SIZE;
  tokens.token = malloc(TOKEN_INIT_SIZE * sizeof(Token));
  return tokens;
}

void token_push(Tokens* tokens, char* lexeme, char* token_type,
                char* token_type_special) {
  if (tokens->length == tokens->capacity) {
    tokens->capacity *= 2;
    tokens->token = realloc(tokens->token, tokens->capacity * sizeof(Token));
  }
  tokens->token[tokens->length++] =
      (Token){lexeme, token_type, token_type_special};
}