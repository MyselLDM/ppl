#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Symbol table for all the reserved words and symbols
const char* CONST_words_keyword[] = {"if",    "else",    "for",   "while",
                                     "true",  "false",   "break", "var",
                                     "print", "continue"};

const char* CONST_words_reserved[] = {"switch", "func",    "string", "return",
                                      "case",   "default", "const",  "null"};

const char* CONST_words_noise[] = {"int", "float", "bool", "char"};

const char* CONST_symbol_delimiters[][2] = {
    {";", "semicolon"}, {"(", "l_paren"}, {")", "r_paren"},  {"{", "l_brace"},
    {"}", "r_brace"},   {",", "comma"},   {"\'", "s_quote"}, {"\"", "d_quote"},
};

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
    {"%", "modulo"},
    {"=", "assignment"},
    {"^", "power"},

};

const char* CONST_symbol_logical[][2] = {
    {"<", "less_than"}, {">", "greater_than"}, {"!=", "not_equal"},
    {"==", "equal"},    {"<=", "less_equal"},  {">=", "greater_equal"}};

const int REGEX_ARRAY_LEN = 9;
const char* REGEX_ARRAY[][2] = {{"commment", REGEX_COMMENT_ALL},
                                {"string", REGEX_STRING},
                                {"float", REGEX_FLOAT},
                                {"integer", REGEX_INT},
                                {"delimiters", REGEX_DELIMITERS},
                                {"text", REGEX_TEXT},
                                {"arithmetic", REGEX_OPERATORS_ARITHMETIC},
                                {"logical", REGEX_OPERATORS_LOGICAL},
                                {"!! INVALID", REGEX_INVALID}};

char* dictionary_lookup_symbol(char* lexeme) {
  // Delimiters Lookup
  for (int i = 0;
       i < sizeof(CONST_symbol_delimiters) / sizeof(CONST_symbol_delimiters[0]);
       i++) {
    if (strcmp(lexeme, CONST_symbol_delimiters[i][0]) == 0) {
      return CONST_symbol_delimiters[i][1];
    }
  }

  // Arithmetic Lookup
  for (int i = 0;
       i < sizeof(CONST_symbol_arithmetic) / sizeof(CONST_symbol_arithmetic[0]);
       i++) {
    if (strcmp(lexeme, CONST_symbol_arithmetic[i][0]) == 0) {
      return CONST_symbol_arithmetic[i][1];
    }
  }

  // Logical Lookup
  for (int i = 0;
       i < sizeof(CONST_symbol_logical) / sizeof(CONST_symbol_logical[0]);
       i++) {
    if (strcmp(lexeme, CONST_symbol_logical[i][0]) == 0) {
      return CONST_symbol_logical[i][1];
    }
  }
  return "";
}

char* dictionary_lookup_text(char* lexeme) {
  // Keyword Lookup
  for (int i = 0;
       i < sizeof(CONST_words_keyword) / sizeof(CONST_words_keyword[0]); i++) {
    if (strcmp(lexeme, CONST_words_keyword[i]) == 0) {
      return "keyword";
    }
  }

  // Reserved Lookup
  for (int i = 0;
       i < sizeof(CONST_words_reserved) / sizeof(CONST_words_reserved[0]);
       i++) {
    if (strcmp(lexeme, CONST_words_reserved[i]) == 0) {
      return "reserved";
    }
  }

  // Noise Lookup
  for (int i = 0; i < sizeof(CONST_words_noise) / sizeof(CONST_words_noise[0]);
       i++) {
    if (strcmp(lexeme, CONST_words_noise[i]) == 0) {
      return "noise";
    }
  }

  return "identifier";
}