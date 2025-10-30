#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"

Tokens tokenizer_token_scan(char* strptr);
void tokenizer_regexes_free();
void tokenizer_regexes_init();

typedef struct {
  const char* name;
  const char* pattern;
} TokenPattern;

#endif