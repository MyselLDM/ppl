#include "tokenizer_manual.h"

#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"
#include "../global/dictionary.h"
#include "token.h"
#include "tokenizer_manual_helper.h"

// Parses a lexeme manually, determines its type and length
char* tokenizer_parse_lexeme(char* strptr, char** token_type,
                             const char** token_type_special) {
  int len = 0;

  // Fast lookup for comments
  if (*strptr == '/' && strptr[1] == '/') {
    if ((len = tokenizer_match_comment(strptr)) > 0) {
      *token_type = "comment";
      RETURN_LEXEME;
    } else {
      RETURN_LEXEME_INVALID;
    }
  }

  // Fast Lookup for delimiters
  if ((len = tokenizer_match_delimiter(strptr)) > 0) {
    *token_type = "delimiter";
    RETURN_LEXEME;
  }

  // Fast Lookup for operators
  if ((len = tokenizer_match_operator(strptr)) > 0) {
    *token_type = "operator";
    RETURN_LEXEME;
  }

  // Fast lookup for Text
  if ((*strptr >= 'a' && *strptr <= 'z') ||
      (*strptr >= 'A' && *strptr <= 'Z') || *strptr == '_') {
    if ((len = tokenizer_match_boolean(strptr)) > 0) {
      *token_type = "constant";
      *token_type_special = "boolean";
      RETURN_LEXEME;
    } else if ((len = tokenizer_match_text(strptr)) > 0) {
      *token_type = "text";
      RETURN_LEXEME;
    } else {
      RETURN_LEXEME_INVALID;
    }
  }

  // Fast lookup for numbers
  if ((*strptr >= '0' && *strptr <= '9') ||
      (*strptr == '-' && (strptr[1] >= '0' && strptr[1] <= '9'))) {
    if ((len = tokenizer_match_float(strptr)) > 0) {
      *token_type = "constant";
      *token_type_special = "float";
      RETURN_LEXEME;
    } else if ((len = tokenizer_match_integer(strptr)) > 0) {
      *token_type = "constant";
      *token_type_special = "integer";
      RETURN_LEXEME;
    } else {
      RETURN_LEXEME_INVALID;
    }
  }

  // Fast lookup for characters
  if (*strptr == '\'') {
    if ((len = tokenizer_match_char(strptr)) > 0) {
      *token_type = "constant";
      *token_type_special = "char";
      RETURN_LEXEME;
    } else {
      RETURN_LEXEME_INVALID;
    }
  }

  // Fast lookup for strings
  if (*strptr == '"') {
    if ((len = tokenizer_match_string(strptr)) > 0) {
      *token_type = "constant";
      *token_type_special = "string";
      RETURN_LEXEME;
    } else {
      RETURN_LEXEME_INVALID;
    }
  }

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

    char* token_type = "";
    const char* token_type_special = "";
    char* lexeme =
        tokenizer_parse_lexeme(strptr, &token_type, &token_type_special);

    // Skip comments
    // Retrieves the proper token type.
    // Skip comments
    if (str_equals(token_type, "comment") == 0) {
      // It's a comment, ignore or push
      token_push(&tokens, lexeme, token_type, token_type_special, line, offset);
    } else {
      // Handle text/constant
      if (str_equals(token_type, "text") == 0) {
        token_type = dictionary_lookup_text(lexeme);
        token_type_special = "";  // optional
      } else if (str_equals(token_type, "constant") == 0) {
        token_type_special = dictionary_lookup_symbol(lexeme);
      }
      token_push(&tokens, lexeme, token_type, token_type_special, line, offset);
    }

    fprintf(fptoken, "%-8d %-8d %-25s %-25s %-25s\n", line, offset, lexeme,
            token_type, token_type_special);

    DEBUG_PRINT("strptr moved %d characters", (int)str_length(lexeme));

    strptr += str_length(lexeme);
    offset += str_length(lexeme);

    DEBUG_PRINT("STRPTR now: %c\n\n", *(strptr));
    free(lexeme);
  }

  fclose(fptoken);
  return tokens;
}
