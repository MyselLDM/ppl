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
    "switch", "func", "return", "case", "default", "break", "continue",
};

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
// Macro to check the current character and move to a new state
#define CHECK_CHAR(c, next_state) \
  do {                            \
    if (*lexeme == c) {           \
      lexeme++;                   \
      goto next_state;            \
    }                             \
  } while (0)

// FSM lookup for keywords, reserved words, noise words, and booleans
const char* dictionary_lookup_text(char* lexeme) {
  if (!lexeme || *lexeme == '\0') return "identifier";

  switch (*lexeme) {
    // -------- Keywords --------
    case 'i':
      lexeme++;
      goto state_i;  // if, int (noise)
    case 'e':
      lexeme++;
      goto state_e;  // else
    case 'f':
      lexeme++;
      goto state_f;  // for, float (noise)
    case 'w':
      lexeme++;
      goto state_w;  // while
    case 'v':
      lexeme++;
      goto state_v;  // var
    case 'p':
      lexeme++;
      goto state_p;  // print
    case 's':
      lexeme++;
      goto state_s;  // switch, string (noise)
    case 'c':
      lexeme++;
      goto state_c;  // case, char (noise), continue
    case 'd':
      lexeme++;
      goto state_d;  // default
    case 'b':
      lexeme++;
      goto state_b;  // break, bool (noise)
    case 'r':
      lexeme++;
      goto state_r;  // return
    default:
      return "identifier";
  }

  // -------- State Chains --------

  // ---- i ----
state_i:
  CHECK_CHAR('f', state_if_end);
  CHECK_CHAR('n', state_int);
  return "identifier";

state_if_end:
  if (*lexeme == '\0') return "keyword";  // "if"
  return "identifier";

state_int:
  if (*lexeme == '\0') return "noise";  // "int"
  return "identifier";

  // ---- e ----
state_e:
  CHECK_CHAR('l', state_el);
  return "identifier";

state_el:
  CHECK_CHAR('s', state_els);
  return "identifier";

state_els:
  CHECK_CHAR('e', state_else_end);
  return "identifier";

state_else_end:
  if (*lexeme == '\0') return "keyword";  // "else"
  return "identifier";

  // ---- f ----
state_f:
  CHECK_CHAR('o', state_fo);
  CHECK_CHAR('l', state_float);
  return "identifier";

state_fo:
  CHECK_CHAR('r', state_for_end);
  return "identifier";

state_for_end:
  if (*lexeme == '\0') return "keyword";  // "for"
  return "identifier";

state_float:
  CHECK_CHAR('a', state_flo_a);
  return "identifier";

state_flo_a:
  CHECK_CHAR('t', state_float_end);
  return "identifier";

state_float_end:
  if (*lexeme == '\0') return "noise";  // "float"
  return "identifier";

  // ---- w ----
state_w:
  CHECK_CHAR('h', state_wh);
  return "identifier";

state_wh:
  CHECK_CHAR('i', state_whi);
  return "identifier";

state_whi:
  CHECK_CHAR('l', state_whil);
  return "identifier";

state_whil:
  CHECK_CHAR('e', state_while_end);
  return "identifier";

state_while_end:
  if (*lexeme == '\0') return "keyword";  // "while"
  return "identifier";

  // ---- v ----
state_v:
  CHECK_CHAR('a', state_va);
  return "identifier";

state_va:
  CHECK_CHAR('r', state_var_end);
  return "identifier";

state_var_end:
  if (*lexeme == '\0') return "keyword";  // "var"
  return "identifier";

  // ---- p ----
state_p:
  CHECK_CHAR('r', state_pr);
  return "identifier";

state_pr:
  CHECK_CHAR('i', state_pri);
  return "identifier";

state_pri:
  CHECK_CHAR('n', state_prin);
  return "identifier";

state_prin:
  CHECK_CHAR('t', state_print_end);
  return "identifier";

state_print_end:
  if (*lexeme == '\0') return "keyword";  // "print"
  return "identifier";

  // ---- s ----
state_s:
  CHECK_CHAR('w', state_sw);  // switch
  CHECK_CHAR('t', state_st);  // string
  return "identifier";

state_sw:
  CHECK_CHAR('i', state_swi);
  return "identifier";

state_swi:
  CHECK_CHAR('t', state_swit);
  return "identifier";

state_swit:
  CHECK_CHAR('c', state_switc);
  return "identifier";

state_switc:
  CHECK_CHAR('h', state_switch_end);
  return "identifier";

state_switch_end:
  if (*lexeme == '\0') return "reserved";  // "switch"
  return "identifier";

state_st:
  CHECK_CHAR('r', state_str);
  return "identifier";

state_str:
  CHECK_CHAR('i', state_stri);
  return "identifier";

state_stri:
  CHECK_CHAR('n', state_strin);
  return "identifier";

state_strin:
  CHECK_CHAR('g', state_string_end);
  return "identifier";

state_string_end:
  if (*lexeme == '\0') return "noise";  // "string"
  return "identifier";

  // ---- c ----
state_c:
  CHECK_CHAR('a', state_ca);  // case, char
  CHECK_CHAR('o', state_co);  // continue
  return "identifier";

state_ca:
  CHECK_CHAR('s', state_cas);
  return "identifier";

state_cas:
  CHECK_CHAR('e', state_case_end);
  return "identifier";

state_case_end:
  if (*lexeme == '\0') return "reserved";  // "case"
  return "identifier";

state_ca2:
  CHECK_CHAR('h', state_char_end);
  return "identifier";

state_char_end:
  if (*lexeme == '\0') return "noise";  // "char"
  return "identifier";

state_co:
  CHECK_CHAR('n', state_con);
  return "identifier";

state_con:
  CHECK_CHAR('t', state_cont);
  return "identifier";

state_cont:
  CHECK_CHAR('i', state_conti);
  return "identifier";

state_conti:
  CHECK_CHAR('n', state_contin);
  return "identifier";

state_contin:
  CHECK_CHAR('u', state_continu);
  return "identifier";

state_continu:
  CHECK_CHAR('e', state_continue_end);
  return "identifier";

state_continue_end:
  if (*lexeme == '\0') return "reserved";  // "continue"
  return "identifier";

  // ---- d ----
state_d:
  CHECK_CHAR('e', state_de);
  return "identifier";

state_de:
  CHECK_CHAR('f', state_def);
  return "identifier";

state_def:
  CHECK_CHAR('a', state_defa);
  return "identifier";

state_defa:
  CHECK_CHAR('u', state_defau);
  return "identifier";

state_defau:
  CHECK_CHAR('l', state_defaul);
  return "identifier";

state_defaul:
  CHECK_CHAR('t', state_default_end);
  return "identifier";

state_default_end:
  if (*lexeme == '\0') return "reserved";  // "default"
  return "identifier";

  // ---- b ----
state_b:
  CHECK_CHAR('r', state_br);  // break
  CHECK_CHAR('o', state_bo);  // bool
  return "identifier";

state_br:
  CHECK_CHAR('e', state_bre);
  return "identifier";

state_bre:
  CHECK_CHAR('a', state_brea);
  return "identifier";

state_brea:
  CHECK_CHAR('k', state_break_end);
  return "identifier";

state_break_end:
  if (*lexeme == '\0') return "reserved";  // "break"
  return "identifier";

state_bo:
  CHECK_CHAR('o', state_boo);
  return "identifier";

state_boo:
  CHECK_CHAR('l', state_bool_end);
  return "identifier";

state_bool_end:
  if (*lexeme == '\0') return "noise";  // "bool"
  return "identifier";

  // ---- r ----
state_r:
  CHECK_CHAR('e', state_re);
  return "identifier";

state_re:
  CHECK_CHAR('t', state_ret);
  return "identifier";

state_ret:
  CHECK_CHAR('u', state_retu);
  return "identifier";

state_retu:
  CHECK_CHAR('r', state_retur);
  return "identifier";

state_retur:
  CHECK_CHAR('n', state_return_end);
  return "identifier";

state_return_end:
  if (*lexeme == '\0') return "reserved";  // "return"
  return "identifier";

  // ---- default fallback ----
  return "identifier";
}
