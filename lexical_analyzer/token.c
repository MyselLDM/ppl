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
  debug_print("%s: tokens struct created\n", __func__);
  return tokens;
}

void token_push(Tokens* tokens, char* lexeme, char* token_type,
                char* token_type_special) {
  if (tokens->length == tokens->capacity) {
    tokens->capacity *= 2;
    tokens->token = realloc(tokens->token, tokens->capacity * sizeof(Token));
    debug_print("%s: tokens struct resized from %d to %d\n", __func__,
                tokens->capacity / 2, tokens->capacity);
  }
  tokens->token[tokens->length++] =
      (Token){lexeme, token_type, token_type_special};
  debug_print("%s: {%s, %s, %s} token pushed\n", __func__, lexeme, token_type,
              token_type_special);
}
