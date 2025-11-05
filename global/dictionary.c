#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>

// Custom string comparison checker
int str_equals(const char* a, const char* b) {
  while (*a && (*a == *b)) {
    a++;
    b++;
  }
  return *(const unsigned char*)a - *(const unsigned char*)b;
}

// Symbol table for all the reserved words and symbols
const char* CONST_words_keyword[] = {"if",    "else",    "for",   "while",
                                     "true",  "false",   "break", "var",
                                     "print", "continue"};

const char* CONST_words_reserved[] = {"switch",  "func",  "return", "case",
                                      "default", "const", "null"};

const char* CONST_words_noise[] = {"int", "float", "bool", "char", "string"};

const char* CONST_symbol_delimiter[][2] = {
    {";", "semicolon"}, {"(", "l_paren"}, {")", "r_paren"},  {"{", "l_brace"},
    {"}", "r_brace"},   {",", "comma"},   {"\'", "s_quote"}, {"\"", "d_quote"},
};

// TODO: Add THE FLOOR DIVIDE SYMBOL
// BOOLEAN VALUES SHOULD BE CONSTANT

const char* CONST_symbol_arithmetic[][2] = {

    // Unary Assignment
    {"++", "increment"},
    {"--", "decrement"},

    // Binary Assignment
    {"+=", "add_assign"},
    {"-=", "subtract_assign"},
    {"*=", "multiply_assign"},
    {"/=", "divide_assign"},
    {"%=", "modulo_assign"},
    {"^=", "power_assign"},

    // N-ary Assignment
    {"*", "multiply"},
    {"+", "add"},
    {"-", "subtract"},
    {"/", "divide"},
    {"\%\%", "floor_divide"},
    {"%", "modulo"},
    {"=", "assignment"},
    {"^", "power"},
};

const char* CONST_symbol_logical[][2] = {
    {"<", "less_than"}, {">", "greater_than"}, {"!=", "not_equal"},
    {"==", "equal"},    {"<=", "less_equal"},  {">=", "greater_equal"},
    {"&&", "and"},      {"||", "or"},          {"!", "not"},
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
                                {"!! INVALID", REGEX_INVALID}};

// This function confirms the symbol of the lexeme
char* dictionary_lookup_symbol(char* lexeme) {
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
char* dictionary_lookup_text(char* lexeme) {
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