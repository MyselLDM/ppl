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

  if ((len = tokenizer_match_comment(strptr)) > 0) {
    *token_type = "comment";
  } else if ((len = tokenizer_match_char(strptr)) > 0) {
    *token_type = "constant";
    *token_type_special = "char";
  } else if ((len = tokenizer_match_string(strptr)) > 0) {
    *token_type = "constant";
    *token_type_special = "string";
  } else if ((len = tokenizer_match_float(strptr)) > 0) {
    *token_type = "constant";
    *token_type_special = "float";
  } else if ((len = tokenizer_match_integer(strptr)) > 0) {
    *token_type = "constant";
    *token_type = "integer";
  } else if ((len = tokenizer_match_delimiter(strptr)) > 0) {
    *token_type = "delimiter";
  } else if ((len = tokenizer_match_operator(strptr)) > 0) {
    *token_type = "operator";
  } else if ((len = tokenizer_match_boolean(strptr)) > 0) {
    *token_type = "constant";
    *token_type_special = "boolean";
  } else if ((len = tokenizer_match_text(strptr)) > 0) {
    *token_type = "text";
  } else {
    len = tokenizer_match_invalid(strptr);
    *token_type = "INVALID";
  }

  DEBUG_PRINT("Found Lexeme with Length %d: %.*s", len, len, strptr);

  // copy lexeme
  char* lexeme = malloc(len + 1);
  for (int i = 0; i < len; i++) lexeme[i] = strptr[i];
  lexeme[len] = '\0';
  DEBUG_PRINT("Returning Lexeme: %s", lexeme);
  return lexeme;
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
    if (str_equals(token_type, "comment") != 0) {
      if (str_equals(token_type, "text") == 0) {
        token_type_special = dictionary_lookup_text(lexeme);
      } else if (str_equals(token_type, "constant") != 0) {
        token_type_special = dictionary_lookup_symbol(lexeme);
      }
      DEBUG_PRINT("{%s, %s, %s} added to file\n", lexeme, token_type,
                  token_type_special);
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
