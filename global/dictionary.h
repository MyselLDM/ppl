#ifndef DICTIONARY_H
#define DICTIONARY_H

// Language Extension
#define LANGUAGE_EXTENSION "bx"

int str_length(char* strptr);

// Token types
typedef enum {
  T_INVALID,
  T_KEYWORD,
  T_RESERVED,
  T_IDENTIFIER,
  T_CONSTANT,
  T_OPERATOR,
  T_DELIMITER,
  T_COMMENT,
  T_NOISE,
  T_TEXT,
  T_UNKNOWN
} TokenType;

// Token type special
typedef enum {
  TS_NONE,  // default if not applicable
  // Keywords
  TS_IF,
  TS_ELSE,
  TS_FOR,
  TS_WHILE,
  TS_VAR,
  TS_PRINT,
  // Reserved
  TS_SWITCH,
  TS_FUNC,
  TS_RETURN,
  TS_CASE,
  TS_DEFAULT,
  TS_BREAK,
  TS_CONTINUE,
  // Noise
  TS_INT,
  TS_FLOAT,
  TS_BOOL,
  TS_CHAR,
  TS_STRING,
  // Constants
  TS_TRUE,
  TS_FALSE,
  TS_CHAR_LITERAL,
  TS_STRING_LITERAL,
  TS_INTEGER_LITERAL,
  TS_FLOAT_LITERAL,
  // Delimiters
  TS_SEMICOLON,
  TS_L_PAREN,
  TS_R_PAREN,
  TS_L_BRACE,
  TS_R_BRACE,
  // Operators
  TS_INCREMENT,
  TS_DECREMENT,
  TS_ADD,
  TS_ADD_ASSIGNMENT,
  TS_SUBTRACT_ASSIGNMENT,
  TS_MULTIPLY_ASSIGNMENT,
  TS_DIVIDE_ASSIGNMENT,
  TS_MODULO_ASSIGNMENT,
  TS_DIVIDE_FLOOR_ASSIGNMENT,
  TS_POWER_ASSIGNMENT,
  TS_SUBTRACT,
  TS_MULTIPLY,
  TS_DIVIDE,
  TS_MODULO,
  TS_DIVIDE_FLOOR,
  TS_ASSIGNMENT,
  TS_POWER,
  TS_EQUAL,
  TS_NOT_EQUAL,
  TS_LESS_EQUAL,
  TS_GREATER_EQUAL,
  TS_AND,
  TS_OR,
  TS_NOT,
  TS_LESS_THAN,
  TS_GREATER_THAN,
  // Text / identifier
  TS_IDENTIFIER,
  // Comment
  TS_COMMENT_LINE,
  TS_COMMENT_BLOCK,
  TS_UNKNOWN
} TokenSpecial;

TokenSpecial dictionary_lookup_text(char* lexeme);
TokenSpecial dictionary_lookup_symbol(char* lexeme);
TokenType token_type_lookup(TokenSpecial ts);
char* tt2str(TokenType token_type);
char* ts2str(TokenSpecial token_special);

#endif
