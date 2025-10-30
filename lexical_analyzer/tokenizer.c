#include "tokenizer.h"

#include <pcre2posix.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../global/debug_print.h"
#include "../global/dictionary.h"
#include "token.h"

#define REGEX_PARSE_INVALID 1
#define REGEX_PARSE_VALID 0

// Precompile regexes once
regex_t compiled_regex[9];

void tokenizer_regexes_init() {
  for (int i = 0; i < REGEX_ARRAY_LEN; i++) {
    regcomp(&compiled_regex[i], REGEX_ARRAY[i][1], REG_EXTENDED);
  }
  debug_print("%s: all (%d) regexes compiled\n", __func__, REGEX_ARRAY_LEN);
}

void tokenizer_regexes_free() {
  for (int i = 0; i < REGEX_ARRAY_LEN; i++) {
    regfree(&compiled_regex[i]);
  }
  debug_print("%s: all (%d) regexes freed\n", __func__, REGEX_ARRAY_LEN);
}

Tokens tokenizer_token_scan(char* strptr) {
  FILE* fptoken = fopen("lexical.log", "w");
  if (!fptoken) {
    perror("Failed to open debug log");
  }

  fprintf(fptoken,
          "%-25s %-25s "
          "%-25s\n============================================================="
          "====\n\n",
          "Lexeme", "Token", "Token Special");

  tokenizer_regexes_init();
  debug_print("%s: created \"lexical.log\"\n", __func__);

  Tokens tokens = token_create();
  int offset = 0;
  int strlength = strlen(strptr);
  regmatch_t reg_matches[1];

  debug_print("%s: STARTING! %d total characters\n", __func__, strlength);

  while (offset < strlength) {
    // Skip contiguous whitespace quickly
    while (offset < strlength &&
           (strptr[offset] == ' ' || strptr[offset] == '\t' ||
            strptr[offset] == '\n')) {
      debug_print("%s: %d/%d:: skipping whitespace\n", __func__, offset,
                  strlength);
      offset++;
    }
    if (offset >= strlength) break;
    debug_print("%s: %d/%d:: scanning letter: \"%c\"\n", __func__, offset,
                strlength, strptr[offset]);

    // Try all precompiled regexes
    for (int i = 0; i < REGEX_ARRAY_LEN; i++) {
      const char* R_IDENTIFIER = REGEX_ARRAY[i][0];
      regex_t* reg_expression = &compiled_regex[i];

      // Only accept matches that start exactly at current offset // because it
      // searches for the first substring that matches the goddamn // regex, so
      // there are stupid instances where you would have to check if // the
      // substring that you are actually looking for is in the  // first
      // match

      if (regexec(reg_expression, strptr + offset, 1, reg_matches, 0) == 0 &&
          reg_matches[0].rm_so == 0) {
        // initializes the str copy phase
        int len = reg_matches[0].rm_eo;

        // Copies over the lexeme
        char* lexeme = malloc(len + 1);
        memcpy(lexeme, strptr + offset, len);
        lexeme[len] = '\0';

        char* token_type = R_IDENTIFIER;
        char* token_type_special = "";

        debug_print("%s: %d/%d:: found \"%s\" with { ln: %d so: %d eo: %d }\n",
                    __func__, offset, strlength, lexeme, len,
                    reg_matches[0].rm_so, reg_matches[0].rm_eo);

        if (strcmp(token_type, "text") == 0) {
          token_type = dictionary_lookup_text(lexeme);
          token_type_special = strdup(lexeme);  // safe copy
        } else {
          token_type_special = dictionary_lookup_symbol(lexeme);
        }

        fprintf(fptoken, "%-25s %-25s %-25s\n", lexeme, token_type,
                token_type_special);

        debug_print(
            "%s: IDENTIFIED: lexeme: %s, token_type: %s, token_type_special:"
            "%s\n",
            __func__, lexeme, token_type, token_type_special);

        if (strcmp(token_type, "comment") != 0) {
          token_push(&tokens, lexeme, token_type, token_type_special);
        } else {
          debug_print("%s: COMMENT IGNORED: %s\n", __func__, lexeme);
        }

        free(lexeme);
        offset += len;
        debug_print("%s: %d/%d increased offset\n", __func__, offset,
                    strlength);
        break;  // matched, go to next token
      }
    }
  }

  tokenizer_regexes_free();
  fclose(fptoken);
  return tokens;
}
