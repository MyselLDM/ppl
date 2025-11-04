#include "tokenizer2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../global/debug_print.h"
#include "token.h"
#include "tokenizer_helper.h"

void tokenizer_token_scan_manual(char* strptr) {
  DEBUG_PRINT("STARTING MANUAL TOKENIZATION", *strptr);
  int line = 1;
  int current_char = 1;

  while (*strptr != '\0') {
    // skips consecutive whitespaces
    while (*strptr == ' ' || *strptr == '\t') {
      DEBUG_PRINT("Whitespace detected, skipping...");
      strptr++;
      current_char++;
    }

    // skips consecutive newlines
    while (*strptr == '\n') {
      DEBUG_PRINT("Newline detected, current new line: %d", ++line);
      strptr++;
      current_char = 0;
    }

    DEBUG_PRINT("current char: %c", *strptr);
    char** lexeme = tokenizer_peek_str(&strptr);
  }
}

char** tokenizer_peek_str(char** strptr) {
  int len = 0;

  switch (**strptr) {
    case '\'':
      len = peek_char(*strptr);
      *strptr += len;
      break;
    default:
      (*strptr)++;
      break;
  }

  return NULL;
}

char* tokenizer_peek_invalid(char** strptr) {
  char* tempchar = *strptr;
  int len = 1;
  while (*tempchar != ' ' || *tempchar != '\t' || *tempchar != '\n' ||
         *tempchar != ' ' || *tempchar != ';' || *tempchar != '(' ||
         *tempchar != ')' || *tempchar != '{' || *tempchar != '}') {
    tempchar++;
  };
  DEBUG_PRINT("FOUND INVALID: \'%.*s\'", len, *strptr);
  return tempchar;
}