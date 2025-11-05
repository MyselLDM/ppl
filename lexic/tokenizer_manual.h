#ifndef TOKENIZER_MANUAL_H
#define TOKENIZER_MANUAL_H

#include "token.h"

#define RETURN_LEXEME                                                 \
  DEBUG_PRINT("Found Lexeme with Length %d: %.*s", len, len, strptr); \
  char* lexeme = malloc(len + 1);                                     \
  for (int i = 0; i < len; i++) lexeme[i] = strptr[i];                \
  lexeme[len] = '\0';                                                 \
  DEBUG_PRINT("Returning Lexeme: %s", lexeme);                        \
  return lexeme

#define RETURN_LEXEME_INVALID            \
  len = tokenizer_match_invalid(strptr); \
  *token_type = "INVALID";               \
  RETURN_LEXEME

Tokens tokenizer_token_scan_manual(char* strptr);

#endif