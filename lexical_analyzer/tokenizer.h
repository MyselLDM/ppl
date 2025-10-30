#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"

Tokens tokenizer_token_scan(char* strptr, int debug);

typedef struct {
  const char* name;
  const char* pattern;
} TokenPattern;

#endif