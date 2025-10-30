#ifndef TOKENIZER_H
#define TOKENIZER_H

char* tokenizer_token_scan(char* strptr);
void tokenizer_token_identify(char* lexeme);

typedef struct {
  const char* name;
  const char* pattern;
} TokenPattern;

#endif