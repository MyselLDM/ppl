// parse_error.c
#include "parse_error.h"

#include "../global/debug_print.h"
#include "bxparser.h"

void print_line_tokens(const Tokens* tokens, size_t line, size_t offset) {
  size_t bufsize = 1024;
  char* buffer = malloc(bufsize);
  if (!buffer) return;
  buffer[0] = '\0';

  for (size_t i = 0; i < tokens->length; i++) {
    if (tokens->token[i].line == line) {
      strncat(buffer, tokens->token[i].lexeme, bufsize - strlen(buffer) - 1);
      strncat(buffer, " ", bufsize - strlen(buffer) - 1);
    }
    if (tokens->token[i].line > line) break;
  }

  if (1) {
    DEBUG_PRINT("%s\n", buffer);
    WRITE_ERR("%s\n", buffer);
  }

  char* spaces = malloc(offset + 2);
  if (!spaces) {
    free(buffer);
    return;
  }
  for (size_t i = 0; i < offset; i++) spaces[i] = ' ';
  spaces[offset] = '^';
  spaces[offset + 1] = '\0';

  DEBUG_PRINT("%s\n", spaces);
  WRITE_ERR("%s\n", spaces);

  free(buffer);
  free(spaces);
}

void parse_error(ParseErrorType type, const char* message, const Token* token,
                 size_t* index, const Tokens* tokens) {
  const char* lexeme = token ? token->lexeme : "EOF";
  size_t line = token ? token->line : 0;
  size_t offset = token ? token->offset : 0;

  DEBUG_PRINT(
      "[PARSE ERROR] Type: %d, '%s' at line %zu, offset %zu (token: '%s')\n",
      type, message, line, offset, lexeme);

  WRITE_ERR(
      "[PARSE ERROR] Type: %d, '%s' at line %zu, offset %zu (token: '%s')\n",
      type, message, line, offset, lexeme);

  print_line_tokens(tokens, line, offset);

  switch (type) {
    case PARSE_ERR_MISSING_SEMICOLON:
      while (*index < tokens->length &&
             CURRENT_TOKEN.token_type_special != TS_SEMICOLON &&
             CURRENT_TOKEN.token_type_special != TS_R_BRACE) {
        (*index)++;
      }
      break;
    case PARSE_ERR_MISSING_PAREN:
      while (*index < tokens->length &&
             CURRENT_TOKEN.token_type_special != TS_R_PAREN &&
             CURRENT_TOKEN.token_type_special != TS_SEMICOLON) {
        (*index)++;
      }
      break;
    case PARSE_ERR_MISSING_BLOCK:
      while (*index < tokens->length &&
             CURRENT_TOKEN.token_type_special != TS_R_BRACE) {
        (*index)++;
      }
      break;
    case PARSE_ERR_UNEXPECTED_TOKEN:
      (*index)++;

      if (*index < tokens->length &&
          CURRENT_TOKEN.token_type_special == TS_NONE) {
        panic_to_sync_point(tokens, index);
      }
      break;
  }
}
