#ifndef TOKENIZER_H
#define TOKENIZER_H

char* tokenizer_token_scan(char* strptr);

typedef struct {
  const char* name;
  const char* pattern;
} TokenPattern;

#endif