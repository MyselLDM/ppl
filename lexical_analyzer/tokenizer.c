#include "tokenizer.h"

#include <pcre2posix.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "token.h"

#define REGEX_PARSE_INVALID 1
#define REGEX_PARSE_VALID 0

Tokens tokenizer_token_scan(char* strptr) {
  Tokens tokens = token_create();

  regex_t reg_expression;
  regmatch_t reg_matches[1];
  int strlength = strlen(strptr);
  int offset = 0;

  while (offset < strlength) {
    // Skip whitespace
    if (strptr[offset] == ' ' || strptr[offset] == '\t' ||
        strptr[offset] == '\n') {
      offset++;
      continue;
    }

    // Walk through all regexes, view "dictionary.h"
    for (int i = 0; i < REGEX_ARRAY_LEN; i++) {
      // Compile regex
      const char* R_IDENTIFIER = REGEX_ARRAY[i][0];
      const char* R_REGEX = REGEX_ARRAY[i][1];

      regcomp(&reg_expression, R_REGEX, REG_EXTENDED);

      // Match starting from current offset
      if (regexec(&reg_expression, strptr + offset, 1, reg_matches, 0) == 0) {
        int start = reg_matches[0].rm_so;
        int end = reg_matches[0].rm_eo;

        // Only accept matches that start exactly at current offset
        // because it searches for the first substring that matches the goddamn
        // regex, so there are stupid instances where you would have to check if
        // the substring that you are actually looking for is in the fucking
        // first match

        // PS THIS TOOK SO LONG TO FIGURE OUT
        if (start == 0) {
          int len = end - start;

          // Get the lexeme
          char* lexeme = malloc(len + 1);
          strncpy(lexeme, strptr + offset, len);
          lexeme[len] = '\0';

          // Get the token types of the lexeme
          char* token_type = R_IDENTIFIER;
          char* token_type_special = "";

          // Retrieves what specific token type the token is
          // The text is a special case because it creates
          if (strcmp(token_type, "text") == 0) {
            token_type = dictionary_lookup_text(lexeme);
            token_type_special = lexeme;
          } else {
            token_type_special = dictionary_lookup_symbol(lexeme);
          }

          if (strcmp(token_type, "comment") != 0) {
            token_push(&tokens, lexeme, token_type, token_type_special);
          }

          printf("%-20s %-15s %-15s\n", lexeme, token_type, token_type_special);

          free(lexeme);

          offset += end;
          regfree(&reg_expression);
          break;  // break AFTER freeing
        }
      }
    }
  }
  return tokens;
}