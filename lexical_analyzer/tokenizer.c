#include "tokenizer.h"

#include <pcre2posix.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// // Regular Expressions for seperating tokens

#define REGEX_STRING "(\"[^\"]*\"|'[^']*')"
#define REGEX_OPERATORS "\\+|\\-|\\*|/|%|\\^|="
#define REGEX_FLOAT "-?[0-9]+\\.[0-9]+"
#define REGEX_INT "-?[0-9]+"
#define REGEX_DELIMITERS "\\(|\\)|{|}|;"
#define REGEX_TEXT "[a-zA-Z_][a-zA-Z0-9_]*"

#define REGEX_ALL                                                 \
  REGEX_STRING "|" REGEX_FLOAT "|" REGEX_INT "|" REGEX_DELIMITERS \
               "|" REGEX_TEXT "|" REGEX_OPERATORS

const int REGEX_LEN = 6;
const char* REGEX_ARRAY[][2] = {
    {"STRING", REGEX_STRING}, {"FLOAT", REGEX_FLOAT},
    {"INT", REGEX_INT},       {"DELIMITERS", REGEX_DELIMITERS},
    {"TEXT", REGEX_TEXT},     {"OPERATORS", REGEX_OPERATORS},
};

char* tokenizer_token_scan(char* strptr) {
  regex_t reg_expression;
  regmatch_t reg_matches[1];
  int strlength = strlen(strptr);
  int offset = 0;

  while (offset < strlength) {
    int matched = 0;

    // Skip whitespace
    if (strptr[offset] == ' ' || strptr[offset] == '\t' ||
        strptr[offset] == '\n') {
      offset++;
      continue;
    }

    for (int i = 0; i < REGEX_LEN; i++) {
      // Compile regex
      const char* R_IDENTIFIER = REGEX_ARRAY[i][0];
      const char* R_REGEX = REGEX_ARRAY[i][1];

      regcomp(&reg_expression, R_REGEX, REG_EXTENDED);

      // Match starting from current offset
      if (regexec(&reg_expression, strptr + offset, 1, reg_matches, 0) == 0) {
        int start = reg_matches[0].rm_so;
        int end = reg_matches[0].rm_eo;

        // Only accept matches that start exactly at current offset
        // PS THIS TOOK SO LONG TO FIGURE OUT
        if (start == 0) {
          int len = end - start;
          char* lexeme = malloc(len + 1);
          strncpy(lexeme, strptr + offset, len);
          lexeme[len] = '\0';

          printf("%-20s %-15s\n", R_IDENTIFIER, lexeme);
          free(lexeme);

          offset += end;  // move past match
          matched = 1;
          regfree(&reg_expression);
          break;  // break AFTER freeing
        }
      }
    }

    // No match → move forward by one char
    if (!matched) {
      offset++;
    }
  }

  return NULL;
}