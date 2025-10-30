#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_INIT_SIZE 16

typedef struct {
  const char* lexeme;
  const char* token_type;
  const char* token_type_special;
} Token;

typedef struct {
  Token* token;
  size_t length;
  size_t capacity;
} Tokens;

#endif