#include "tokenizer_manual.h"

#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"
#include "../global/dictionary.h"
#include "token.h"
#include "tokenizer_manual_helper.h"

int str_length(char* strptr) {
  int len = 0;
  while (*strptr != '\0') {
    len++;
    strptr++;
  };
  return len;
}

// Parses a lexeme manually, determines its type and length
char* tokenizer_parse_lexeme(char* strptr, char** token_type) {
  int len = 0;

  if ((len = tokenizer_match_comment(strptr)) > 0) {
    *token_type = "comment";
  } else if ((len = tokenizer_match_char(strptr)) > 0) {
    *token_type = "character";
  } else if ((len = tokenizer_match_string(strptr)) > 0) {
    *token_type = "string";
  } else if ((len = tokenizer_match_number(strptr)) > 0) {
    *token_type = "number";
  } else if ((len = tokenizer_match_delimiter(strptr)) > 0) {
    *token_type = "delimiter";
  } else if ((len = tokenizer_match_operator(strptr)) > 0) {
    *token_type = "operator";
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
  FILE* fptoken = fopen("lexical.log", "w");
  if (!fptoken) {
    perror("Failed to open debug log");
  }

  fprintf(fptoken,
          "%-25s %-25s "
          "%-25s\n============================================================="
          "====\n\n",
          "Lexeme", "Token", "Token Special");

  Tokens tokens = token_create();
  int line = 1;

  while (*strptr != '\0') {
    // Skip whitespace
    while (*strptr == ' ' || *strptr == '\t') {
      strptr++;
      DEBUG_PRINT("Skipping whitespace");
    }
    while (*strptr == '\n') {
      DEBUG_PRINT("New Line: %d", ++line);
      strptr++;
    }

    if (*strptr == '\0') break;

    char* token_type = "";
    char* token_type_special;
    char* lexeme = tokenizer_parse_lexeme(strptr, &token_type);

    // Skip comments
    if (str_equals(token_type, "comment") != 0) {
      token_type_special = (str_equals(token_type, "text") == 0)
                               ? dictionary_lookup_text(lexeme)
                               : dictionary_lookup_symbol(lexeme);
      token_push(&tokens, lexeme, token_type, token_type_special, line);
    }

    fprintf(fptoken, "%-25s %-25s %-25s\n", lexeme, token_type,
            token_type_special);
    DEBUG_PRINT("{%s, %s, %s} added to file\n", lexeme, token_type,
                token_type_special);

    DEBUG_PRINT("strptr moved %d characters", (int)str_length(lexeme));

    strptr += str_length(lexeme);

    DEBUG_PRINT("strptr now: %c", strptr);
    free(lexeme);
  }

  fclose(fptoken);
  return tokens;
}
