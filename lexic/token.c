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

// Pushes a token into the tokens struct
void token_push(Tokens* tokens, char* lexeme, TokenType token_type,
                TokenSpecial token_type_special, size_t line, size_t offset) {
  if (tokens->length == tokens->capacity) {
    tokens->capacity *= 2;
    tokens->token = realloc(tokens->token, tokens->capacity * sizeof(Token));
    DEBUG_PRINT("tokens struct resized from %d to %d\n", tokens->capacity / 2,
                tokens->capacity);
  }
  tokens->token[tokens->length++] =
      (Token){line, offset, lexeme, token_type, token_type_special};
  DEBUG_PRINT("{%s, %s, %s} at line %d offset %d token pushed\n", lexeme,
              tt2str(token_type), ts2str(token_type_special), line, offset);
}

// Frees the memory used by the tokens array (shrinks it to exact length)
void token_optimize(Tokens* tokens) {
  if (tokens->length == 0) {
    free(tokens->token);
    tokens->token = NULL;
    tokens->capacity = 0;
    return;
  }

  if (tokens->length < tokens->capacity) {
    Token* new_array = realloc(tokens->token, tokens->length * sizeof(Token));
    if (new_array) {
      tokens->token = new_array;
      tokens->capacity = tokens->length;
      DEBUG_PRINT("Tokens array shrunk to fit %zu elements", tokens->length);
    }
    // If realloc fails, we still keep the old array to avoid losing data
  }
}