#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>

// Custom strlength
int str_length(char* strptr) {
  int len = 0;
  while (*strptr != '\0') {
    len++;
    strptr++;
  };
  return len;
}

// Custom string comparison checker
int str_equals(const char* a, const char* b) {
  while (*a && *b) {
    if (*a != *b) return 1;
    a++;
    b++;
  }
  return *a != *b;
}

// Symbol table for all the reserved words and symbols
const char* CONST_words_keyword[] = {"if",    "else", "for",
                                     "while", "var",  "print"};

const char* CONST_words_reserved[] = {
    "switch",   "func",   "return", "case",    "default", "const",   "null",
    "static",   "goto",   "do",     "enum",    "struct",  "typedef", "sizeof",
    "import",   "export", "extern", "inline",  "yield",   "await",   "break",
    "continue", "try",    "catch",  "finally", "throw"};

const char* CONST_words_noise[] = {"int", "float", "bool", "char", "string"};

const char* CONST_symbol_delimiter[][2] = {{";", "semicolon"},
                                           {"(", "l_paren"},
                                           {")", "r_paren"},
                                           {"{", "l_brace"},
                                           {"}", "r_brace"}};

const char* CONST_constant_boolean[] = {"true", "false"};

const char* CONST_symbol_arithmetic[][2] = {

    // Unary Assignment
    {"++", "increment"},
    {"--", "decrement"},

    // N-ary Assignment
    {"*", "multiply"},
    {"+", "add"},
    {"-", "subtract"},
    {"/", "divide"},
    {"%%", "divide_floor"},
    {"%", "modulo"},
    {"=", "assignment"},
    {"^", "power"},
};

const char* CONST_symbol_logical[][2] = {
    {"!=", "not_equal"},   {"==", "equal"},
    {"<=", "less_equal"},  {">=", "greater_equal"},
    {"&&", "and"},         {"||", "or"},
    {"!", "not"},          {"<", "less_than"},
    {">", "greater_than"},
};

const int REGEX_ARRAY_LEN = 10;
const char* REGEX_ARRAY[][2] = {{"comment", REGEX_COMMENT_ALL},
                                {"character", REGEX_CHAR},
                                {"string", REGEX_STRING},
                                {"float", REGEX_FLOAT},
                                {"integer", REGEX_INT},
                                {"delimiter", REGEX_DELIMITER},
                                {"text", REGEX_TEXT},
                                {"arithmetic", REGEX_OPERATORS_ARITHMETIC},
                                {"logical", REGEX_OPERATORS_LOGICAL},
                                {"INVALID", REGEX_INVALID}};

// This function confirms the symbol of the lexeme
const char* dictionary_lookup_symbol(char* lexeme) {
  // Delimiters Lookup
  for (int i = 0;
       i < sizeof(CONST_symbol_delimiter) / sizeof(CONST_symbol_delimiter[0]);
       i++) {
    if (str_equals(lexeme, CONST_symbol_delimiter[i][0]) == 0) {
      return CONST_symbol_delimiter[i][1];
    }
  }

  // Arithmetic Lookup
  for (int i = 0;
       i < sizeof(CONST_symbol_arithmetic) / sizeof(CONST_symbol_arithmetic[0]);
       i++) {
    if (str_equals(lexeme, CONST_symbol_arithmetic[i][0]) == 0) {
      return CONST_symbol_arithmetic[i][1];
    }
  }

  // Logical Lookup
  for (int i = 0;
       i < sizeof(CONST_symbol_logical) / sizeof(CONST_symbol_logical[0]);
       i++) {
    if (str_equals(lexeme, CONST_symbol_logical[i][0]) == 0) {
      return CONST_symbol_logical[i][1];
    }
  }
  return "";
}

// This function confirms the type of the text lexeme, it returns identifier as
// a default fallback This is due to that the identifier is the final fallback
// that isnt an invalid string.
const char* dictionary_lookup_text(char* lexeme) {
  // Keyword Lookup
  for (int i = 0;
       i < sizeof(CONST_words_keyword) / sizeof(CONST_words_keyword[0]); i++) {
    if (str_equals(lexeme, CONST_words_keyword[i]) == 0) {
      return "keyword";
    }
  }

  // Reserved Lookup
  for (int i = 0;
       i < sizeof(CONST_words_reserved) / sizeof(CONST_words_reserved[0]);
       i++) {
    if (str_equals(lexeme, CONST_words_reserved[i]) == 0) {
      return "reserved";
    }
  }

  // Noise Lookup
  for (int i = 0; i < sizeof(CONST_words_noise) / sizeof(CONST_words_noise[0]);
       i++) {
    if (str_equals(lexeme, CONST_words_noise[i]) == 0) {
      return "noise";
    }
  }

  return "identifier";
}