#ifndef DICTIONARY_H
#define DICTIONARY_H

// Language Extension
#define LANGUAGE_EXTENSION "bx"

// Regular Expressions for seperating tokens
#define REGEX_STRING "(\"[^\"]*\"|'[^']*')"
#define REGEX_OPERATORS_ARITHMETIC "\\+\\+?=?|\\-\\-?=?|\\*=?|/=?|%=?|\\^=?|="
#define REGEX_OPERATORS_LOGICAL "<=?|>=?|==|!=?|&&|\\|\\|"
#define REGEX_FLOAT "-?[0-9]+\\.[0-9]+"
#define REGEX_INT "-?[0-9]+"
#define REGEX_DELIMITER "\\(|\\)|{|}|;"
#define REGEX_TEXT "[a-zA-Z_][a-zA-Z0-9_]*"

// Regex for invalid tokens
#define REGEX_INVALID "[^ \t\n]+"

#define REGEX_COMMENT_INLINE "//[^\n/]+"
#define REGEX_COMMENT_BLOCK "///[^*]*///"
#define REGEX_COMMENT_ALL REGEX_COMMENT_INLINE "|" REGEX_COMMENT_BLOCK

// Union regex just in case for testing purposes
#define REGEX_ALL                                                \
  REGEX_STRING "|" REGEX_FLOAT "|" REGEX_INT "|" REGEX_DELIMITER \
               "|" REGEX_TEXT "|" REGEX_OPERATORS_ARITHMETIC     \
               "|" REGEX_OPERATORS_LOGICAL

// Lookup table for constants
// extern const char* CONST_symbol_logical[9];
extern const char* CONST_words_keyword[10];
extern const char* CONST_words_reserved[8];
extern const char* CONST_words_noise[4];
extern const char* CONST_symbol_delimiter[8][2];
extern const char* CONST_symbol_arithmetic[15][2];
extern const char* CONST_symbol_logical[9][2];

extern const int REGEX_ARRAY_LEN;
extern const char* REGEX_ARRAY[9][2];

char* dictionary_lookup_symbol(char* lexeme);
char* dictionary_lookup_text(char* lexeme);

#endif
