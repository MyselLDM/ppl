#include "tokenizer.h"

#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"
#include "../global/dictionary.h"
#include "token.h"
#include "tokenizer_helper.h"

#define RETURN_LEXEME_INVALID                                             \
  return make_lexeme(strptr, tokenizer_match_invalid(strptr), token_type, \
                     token_type_special, T_INVALID, TS_NONE);

// Makes the lexeme length
// Helper: allocates lexeme, sets token types, and returns the string
static char* make_lexeme(char* strptr, int len, TokenType* token_type,
                         TokenSpecial* token_type_special, TokenType ttype,
                         TokenSpecial tspecial) {
  *token_type = ttype;
  *token_type_special = tspecial;

  char* lexeme = malloc(len + 1);
  for (int i = 0; i < len; i++) lexeme[i] = strptr[i];
  lexeme[len] = '\0';

  DEBUG_PRINT("Found Lexeme with Length %d: %.*s", len, len, strptr);
  DEBUG_PRINT("Returning Lexeme: %s", lexeme);

  return lexeme;
}

// Parses a lexeme manually, determines its type and length
char* tokenizer_parse_lexeme(char* strptr, TokenType* token_type,
                             TokenSpecial* token_type_special) {
  int len = 0;

  // Comments
  if (*strptr == '/' && strptr[1] == '/') {
    len = tokenizer_match_comment(strptr);
    if (len > 0) {
      TokenSpecial ts = (*strptr == '/' && strptr[2] == '/') ? TS_COMMENT_BLOCK
                                                             : TS_COMMENT_LINE;
      return make_lexeme(strptr, len, token_type, token_type_special, T_COMMENT,
                         ts);
    } else {
      RETURN_LEXEME_INVALID;
    }
  }

  // Numbers
  if ((*strptr >= '0' && *strptr <= '9') ||
      (*strptr == '-' && strptr[1] >= '0' && strptr[1] <= '9')) {
    if ((len = tokenizer_match_float(strptr)) > 0)
      return make_lexeme(strptr, len, token_type, token_type_special,
                         T_CONSTANT, TS_FLOAT);
    else if ((len = tokenizer_match_integer(strptr)) > 0)
      return make_lexeme(strptr, len, token_type, token_type_special,
                         T_CONSTANT, TS_INTEGER_LITERAL);
    else
      RETURN_LEXEME_INVALID;
  }

  // Characters
  if (*strptr == '\'') {
    len = tokenizer_match_char(strptr);
    if (len > 0)
      return make_lexeme(strptr, len, token_type, token_type_special,
                         T_CONSTANT, TS_CHAR);
    else
      RETURN_LEXEME_INVALID;
  }

  // Strings
  if (*strptr == '"') {
    len = tokenizer_match_string(strptr);
    if (len > 0)
      return make_lexeme(strptr, len, token_type, token_type_special,
                         T_CONSTANT, TS_STRING);
    else
      RETURN_LEXEME_INVALID;
  }

  DEBUG_PRINT("STRINGPOINTER %c entering the TEXT LOOP", *strptr);
  // Text / Keywords / Booleans
  if ((*strptr >= 'a' && *strptr <= 'z') ||
      (*strptr >= 'A' && *strptr <= 'Z') || *strptr == '_') {
    TokenSpecial ts = dictionary_lookup_text(strptr, &len);
    if (len > 0) {
      char* temp = malloc(len + 1);
      for (int i = 0; i < len; i++) temp[i] = strptr[i];
      temp[len] = '\0';

      TokenType t = token_type_lookup(ts);
      free(temp);
      return make_lexeme(strptr, len, token_type, token_type_special, t, ts);
    }
  }

  // Delimiters
  if (len == 0) {
    TokenSpecial ts = dictionary_lookup_symbol(strptr, &len);
    TokenType tt = token_type_lookup(ts);
    if (len > 0) {
      return make_lexeme(strptr, len, token_type, token_type_special, tt, ts);
    }
  }

  // Fallback invalid
  RETURN_LEXEME_INVALID;
}

// Main scanning loop
Tokens tokenizer_token_scan_manual(char* strptr) {
  FILE* fptoken = fopen("Symbol Table.txt", "w");
  if (!fptoken) {
    perror("Failed to open debug log");
  }

  fprintf(fptoken,
          "%-8s %-8s %-25s %-25s "
          "%-25s\n============================================================="
          "====\n\n",
          "Line", "Offset", "Lexeme", "Token", "Token Special");

  Tokens tokens = token_create();
  int line = 1;
  int offset = 0;

  while (*strptr != '\0') {
    // Skip whitespace and new lines
    // condensed on a singlular while loop for repetitive events and debugging
    while (*strptr == ' ' || *strptr == '\t' || *strptr == '\r' ||
           *strptr == '\n') {
      if (*strptr == '\n') {
        DEBUG_PRINT("New Line: %d", ++line);
        offset = 0;
      } else {
        DEBUG_PRINT("Skipping whitespace");
        offset++;
      }
      strptr++;
    }

    if (*strptr == '\0') break;

    TokenType token_type = 0;
    TokenSpecial token_type_special = 0;
    char* lexeme =
        tokenizer_parse_lexeme(strptr, &token_type, &token_type_special);

    // Skip comments
    // Retrieves the proper token type.
    if (token_type != T_COMMENT) {
      DEBUG_PRINT("{%s, %s, %s} added to file\n", lexeme, tt2str(token_type),
                  ts2str(token_type_special));
      token_push(&tokens, lexeme, token_type, token_type_special, line, offset);
    }

    fprintf(fptoken, "%-8d %-8d %-25s %-25s %-25s\n", line, offset, lexeme,
            tt2str(token_type), ts2str(token_type_special));

    DEBUG_PRINT("strptr moved %d characters", (int)str_length(lexeme));

    strptr += str_length(lexeme);
    offset += str_length(lexeme);

    DEBUG_PRINT("STRPTR now: %c\n\n", *(strptr));
    free(lexeme);
  }

  fclose(fptoken);
  return tokens;
}
