#ifndef PARSE_ERROR_H
#define PARSE_ERROR_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"
#include "../lexic/token.h"
#include "ast.h"

typedef enum {
  PARSE_ERR_UNEXPECTED_TOKEN,
  PARSE_ERR_MISSING_SEMICOLON,
  PARSE_ERR_MISSING_PAREN,
  PARSE_ERR_MISSING_BLOCK,
  PARSE_ERR_UNKNOWN
} ParseErrorType;

#define WRITE_ERR(...)                                                 \
  FILE* f = fopen("logs/error - syntax.log", "a");                     \
  if (!f) {                                                            \
    fprintf(stderr, "Failed to open syntax_errors.txt for writing\n"); \
  } else {                                                             \
    fprintf(f, __VA_ARGS__);                                           \
    fclose(f);                                                         \
  }

#define PARSE_ERROR_UNEXPECTED_TOKEN(msg)                                     \
  parse_error(PARSE_ERR_UNEXPECTED_TOKEN, "Unexpected token", &CURRENT_TOKEN, \
              index, tokens)

#define PARSE_ERROR_SEMICOLON()                                            \
  parse_error(PARSE_ERR_MISSING_SEMICOLON, "Expected ';'", &CURRENT_TOKEN, \
              index, tokens)

#define PARSE_ERROR_PAREN()                                                   \
  parse_error(PARSE_ERR_MISSING_PAREN, "Expected '(' or ')'", &CURRENT_TOKEN, \
              index, tokens)

#define PARSE_ERROR_BLOCK()                                                   \
  parse_error(PARSE_ERR_MISSING_BLOCK, "Expected block '{}'", &CURRENT_TOKEN, \
              index, tokens)

#define CHECK_SEMICOLON                                   \
  if (CURRENT_TOKEN.token_type_special != TS_SEMICOLON) { \
    PARSE_ERROR_SEMICOLON();                              \
  } else {                                                \
    (*index)++;                                           \
  }

#define NEXT_TOKEN()                                       \
  if (CURRENT_TOKEN.token_type_special == TS_NONE) {       \
    DEBUG_PRINT("[PARSE ERROR] Found Invalid Token: %s\n", \
                CURRENT_TOKEN.lexeme);                     \
    WRITE_ERR("[PARSE ERROR] Found Invalid Token: %s\n",   \
              CURRENT_TOKEN.lexeme);                       \
    panic_to_sync_point(tokens, index);                    \
  } else {                                                 \
    (*index)++;                                            \
  }

void print_line_tokens(const Tokens* tokens, size_t line, size_t offset);
void parse_error(ParseErrorType type, const char* message, const Token* token,
                 size_t* index, const Tokens* tokens);

static inline void panic_to_sync_point(const Tokens* tokens, size_t* index) {
  while (*index < tokens->length) {
    Token t = tokens->token[*index];

    // Stop at a safe statement boundary
    if (t.token_type_special == TS_SEMICOLON ||
        t.token_type_special == TS_R_BRACE || t.token_type_special == TS_VAR ||
        t.token_type_special == TS_PRINT || t.token_type_special == TS_IF ||
        t.token_type_special == TS_WHILE || t.token_type_special == TS_FOR) {
      break;
    }

    (*index)++;  // skip bad token
  }
}

#endif
