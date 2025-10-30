#include "special_characters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* CONST_words_keyword[] = {"if",    "else",    "for",   "while",
                                     "true",  "false",   "break", "var",
                                     "print", "continue"};

const char* CONST_words_reserved[] = {"switch", "func",    "string", "return",
                                      "case",   "default", "const",  "null"};

const char* CONST_words_noise[] = {"int", "float", "bool", "char"};

const char* CONST_words_datatype[] = {"int", "float", "bool", "char"};

const char* CONST_SC_delimiters[] = {";", "(", ")", "{", "}", ",", "\'"};

const char* CONST_SC_arithmetic[] = {"+", "-", "*", "/", "%", "=", "^"};

const char* CONST_SC_logical[] = {"greater", "lesser", "not",    "equals",
                                  "and",     "or",     "nequals"};

int main();