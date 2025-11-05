#include "tokenizer.h"

#if defined(_WIN32) || defined(_WIN64)
// Windows build
#include <pcre2posix.h>
#else
// macOS or Linux (POSIX systems)
#include <regex.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../global/debug_print.h"
#include "../global/dictionary.h"
#include "../lexic/token.h"

#define REGEX_PARSE_INVALID 1
#define REGEX_PARSE_VALID 0

// Precompile regexes once
regex_t compiled_regex[9];

/*
DO NOT TOUCH DO NOT TOUCH DO NOT TOUCH DO NOT TOUCH
DO NOT TOUCH DO NOT TOUCH DO NOT TOUCH DO NOT TOUCH
DO NOT TOUCH DO NOT TOUCH DO NOT TOUCH DO NOT TOUCH
DO NOT TOUCH DO NOT TOUCH DO NOT TOUCH DO NOT TOUCH
DO NOT TOUCH DO NOT TOUCH DO NOT TOUCH DO NOT TOUCH
*/

void tokenizer_regexes_init() {
  for (int i = 0; i < REGEX_ARRAY_LEN; i++) {
    regcomp(&compiled_regex[i], REGEX_ARRAY[i][1], REG_EXTENDED);
  }
  DEBUG_PRINT("all (%d) regexes compiled\n", REGEX_ARRAY_LEN);
}

void tokenizer_regexes_free() {
  for (int i = 0; i < REGEX_ARRAY_LEN; i++) {
    regfree(&compiled_regex[i]);
  }
  DEBUG_PRINT("all (%d) regexes freed\n", REGEX_ARRAY_LEN);
}

Tokens tokenizer_token_scan(char* strptr) {
  FILE* fptoken = fopen("Symbol Table (OLD).txt", "w");
  if (!fptoken) {
    perror("Failed to open debug log");
  }

  fprintf(fptoken,
          "%-8s %-8s %-25s %-25s "
          "%-25s\n============================================================="
          "====\n\n",
          "Line", "Offset", "Lexeme", "Token", "Token Special");

  tokenizer_regexes_init();
  DEBUG_PRINT("created \"lexical.log\"", __func__);

  Tokens tokens = token_create();
  int offset = 0;
  int charoffset = 0;
  size_t line = 1;
  int strlength = str_length(strptr);
  regmatch_t reg_matches[1];

  DEBUG_PRINT("STARTING! %d total characters", strlength);

  while (offset < strlength) {
    // Skip contiguous whitespace quickly
    while (offset < strlength &&
           (strptr[offset] == ' ' || strptr[offset] == '\t')) {
      DEBUG_PRINT("%d/%d:: skipping whitespace\n", offset++, strlength);
      charoffset++;
    }

    // Skip contiguous newlines quickly
    while (offset < strlength && strptr[offset] == '\n') {
      DEBUG_PRINT("%d/%d:: NEWLINE detected, incrementing line to %d\n",
                  offset++, strlength, ++line);
    }

    if (offset >= strlength) break;  // Quick escape for the case of EOF
    DEBUG_PRINT("%d/%d:: scanning letter: \"%c\"", offset, strlength,
                strptr[offset]);

    // Try all precompiled regexes
    for (int i = 0; i < REGEX_ARRAY_LEN; i++) {
      const char* R_IDENTIFIER = REGEX_ARRAY[i][0];
      regex_t* reg_expression = &compiled_regex[i];

      // Only accept matches that start exactly at current offset // because it
      // searches for the first substring that matches the  // regex, so
      // there are  instances where you would have to check if // the
      // substring that you are actually looking for is in the  // first
      // match

      // no i will not update this to include ^, it seems so quirky

      if (regexec(reg_expression, strptr + offset, 1, reg_matches, 0) == 0 &&
          reg_matches[0].rm_so == 0) {
        // initializes the str copy phase
        int len = reg_matches[0].rm_eo;

        // Copies over the lexeme
        char* lexeme = malloc(len + 1);
        memcpy(lexeme, strptr + offset, len);
        lexeme[len] = '\0';

        // Default token types
        char* token_type = R_IDENTIFIER;
        char* token_type_special = "";

        DEBUG_PRINT("%d/%d:: found \"%s\" with { ln: %d so: %d eo: %d }",
                    offset, strlength, lexeme, len, reg_matches[0].rm_so,
                    reg_matches[0].rm_eo);

        // Group similar regex identifiers into broader classes
        if (str_equals(R_IDENTIFIER, "arithmetic") == 0 ||
            str_equals(R_IDENTIFIER, "logical") == 0 ||
            str_equals(R_IDENTIFIER, "assignment") == 0) {
          token_type = "operator";
          token_type_special = dictionary_lookup_symbol(lexeme);
        }

        else if (str_equals(R_IDENTIFIER, "character") == 0 ||
                 str_equals(R_IDENTIFIER, "string") == 0 ||
                 str_equals(R_IDENTIFIER, "float") == 0 ||
                 str_equals(R_IDENTIFIER, "integer") == 0 ||
                 str_equals(R_IDENTIFIER, "boolean") == 0) {
          token_type = "constant";
          token_type_special = R_IDENTIFIER;  // char, string, etc.
        }

        else if (str_equals(R_IDENTIFIER, "text") == 0) {
          token_type = "text";
          token_type_special = dictionary_lookup_text(lexeme);
        }

        else if (str_equals(R_IDENTIFIER, "delimiter") == 0) {
          token_type_special = dictionary_lookup_symbol(lexeme);
        }

        // Prints the lexemes to a file
        fprintf(fptoken, "%-8d %-8d %-25s %-25s %-25s\n", line, charoffset,
                lexeme, token_type, token_type_special);

        DEBUG_PRINT(
            "IDENTIFIED: lexeme: %s, token_type: %s, token_type_special:"
            "%s",
            lexeme, token_type, token_type_special);

        if (str_equals(token_type, "comment") != 0) {
          token_push(&tokens, lexeme, token_type, token_type_special, line,
                     charoffset);
        } else {
          DEBUG_PRINT("COMMENT IGNORED: %s", lexeme);
        }

        // Free allocated memory
        free(lexeme);
        offset += len;
        charoffset += len;
        DEBUG_PRINT("%d/%d increased offset", offset, strlength);
        break;
      }
    }
  }

  tokenizer_regexes_free();
  fclose(fptoken);
  return tokens;
}

// char* tokenizer_parse_lexeme2(char* strptr, char** token_type,
//                               const char** token_type_special) {
//   int len = 0;
//   if ((len = tokenizer_match_comment(strptr)) > 0) {
//     *token_type = "comment";
//   } else if ((len = tokenizer_match_char(strptr)) > 0) {
//     *token_type = "constant";
//     *token_type_special = "char";
//   } else if ((len = tokenizer_match_string(strptr)) > 0) {
//     *token_type = "constant";
//     *token_type_special = "string";
//   } else if ((len = tokenizer_match_float(strptr)) > 0) {
//     *token_type = "constant";
//     *token_type_special = "float";
//   } else if ((len = tokenizer_match_integer(strptr)) > 0) {
//     *token_type = "constant";
//     *token_type = "integer";
//   } else if ((len = tokenizer_match_delimiter(strptr)) > 0) {
//     *token_type = "delimiter";
//   } else if ((len = tokenizer_match_operator(strptr)) > 0) {
//     *token_type = "operator";
//   } else if ((len = tokenizer_match_boolean(strptr)) > 0) {
//     *token_type = "constant";
//     *token_type_special = "boolean";
//   } else if ((len = tokenizer_match_text(strptr)) > 0) {
//     *token_type = "text";
//   } else {
//     len = tokenizer_match_invalid(strptr);
//     *token_type = "INVALID";
//   }

//   DEBUG_PRINT("Found Lexeme with Length %d: %.*s", len, len, strptr);

//   // copy lexeme
//   char* lexeme = malloc(len + 1);
//   for (int i = 0; i < len; i++) lexeme[i] = strptr[i];
//   lexeme[len] = '\0';
//   DEBUG_PRINT("Returning Lexeme: %s", lexeme);
//   return lexeme;
// }
