#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>

#include "debug_print.h"

#define ISALPHANUM                                                             \
  ((*lexeme >= 'a' && *lexeme <= 'z') || (*lexeme >= 'A' && *lexeme <= 'Z') || \
   (*lexeme >= '0' && *lexeme <= '9') || (*lexeme == '_'))

#define MATCH_IDENTIFIER                                                 \
  do {                                                                   \
    while (ISALPHANUM) {                                                 \
      lexeme++;                                                          \
      DEBUG_PRINT("IDENTIFIER '%c' found: incrementing ptr", *(lexeme)); \
      (*len)++;                                                          \
    }                                                                    \
    DEBUG_PRINT("returning len: %d", *len);                              \
    return TS_IDENTIFIER;                                                \
  } while (0)

// Automata Macro for checking the next character
#define CHECK_CHAR(c, next_state)                             \
  do {                                                        \
    if (*lexeme == c) {                                       \
      lexeme++;                                               \
      DEBUG_PRINT("KEYWORD '%c' found: incrementing ptr", c); \
      (*len)++;                                               \
      goto next_state;                                        \
    }                                                         \
  } while (0)

// Custom strlength
int str_length(char* strptr) {
  int len = 0;
  while (*strptr != '\0') {
    len++;
    strptr++;
  };
  return len;
}

TokenSpecial dictionary_lookup_text(char* lexeme, int* len) {
  (*len) = 0;

  if (*lexeme == '\0') return TS_IDENTIFIER;

  DEBUG_PRINT("Starting with '%c'", *lexeme);
  (*len)++;
  switch (*lexeme) {
    case 'i':
      lexeme++;
      goto state_i;  // if, int
    case 'e':
      lexeme++;
      goto state_e;  // else
    case 'f':
      lexeme++;
      goto state_f;  // for, float, false
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
      goto state_s;  // switch, string
    case 'c':
      lexeme++;
      goto state_c;  // case, char, continue
    case 'd':
      lexeme++;
      goto state_d;  // default
    case 'b':
      lexeme++;
      goto state_b;  // break, bool
    case 'r':
      lexeme++;
      goto state_r;  // return
    case 't':
      lexeme++;
      goto state_t;  // true
    default:
      *len = 0;
      MATCH_IDENTIFIER;
  }

  // -------- i --------
state_i:
  if (*lexeme == 'f') {
    lexeme++;
    (*len)++;
    goto state_if_end;
  }
  if (*lexeme == 'n') {
    lexeme++;
    (*len)++;
    goto state_int;
  }
  MATCH_IDENTIFIER;
state_if_end:
  if (!ISALPHANUM) return TS_IF;  // if
  MATCH_IDENTIFIER;
state_int:
  if (!ISALPHANUM) return TS_INT;  // int
  MATCH_IDENTIFIER;

  // -------- e --------
state_e:
  CHECK_CHAR('l', state_el);
  MATCH_IDENTIFIER;
state_el:
  CHECK_CHAR('s', state_els);
  MATCH_IDENTIFIER;
state_els:
  CHECK_CHAR('e', state_else_end);
  MATCH_IDENTIFIER;
state_else_end:
  if (!ISALPHANUM) return TS_ELSE;  // else
  MATCH_IDENTIFIER;

  // -------- f --------
state_f:
  CHECK_CHAR('o', state_fo);  // for
  CHECK_CHAR('l', state_fl);  // float
  CHECK_CHAR('a', state_fa);  // false
  CHECK_CHAR('u', state_fu);  // func
  MATCH_IDENTIFIER;

  // for
state_fo:
  CHECK_CHAR('r', state_for_end);
  MATCH_IDENTIFIER;
state_for_end:
  if (!ISALPHANUM) return TS_FOR;  // for
  MATCH_IDENTIFIER;

  // handle both "float"
state_fl:
  CHECK_CHAR('o', state_flo);  // float
  MATCH_IDENTIFIER;
  // float
state_flo:
  CHECK_CHAR('a', state_floa);
  MATCH_IDENTIFIER;
state_floa:
  CHECK_CHAR('t', state_float_end);
  MATCH_IDENTIFIER;
state_float_end:
  if (!ISALPHANUM) return TS_FLOAT;  // float
  MATCH_IDENTIFIER;

  // false
state_fa:
  CHECK_CHAR('l', state_fal);
  MATCH_IDENTIFIER;
state_fal:
  CHECK_CHAR('s', state_fals);
  MATCH_IDENTIFIER;
state_fals:
  CHECK_CHAR('e', state_false_end);
  MATCH_IDENTIFIER;
state_false_end:
  if (!ISALPHANUM) return TS_FALSE;  // false
  MATCH_IDENTIFIER;

state_fu:
  CHECK_CHAR('n', state_fun);
  MATCH_IDENTIFIER;
state_fun:
  CHECK_CHAR('c', state_func_end);
  MATCH_IDENTIFIER;
state_func_end:
  if (!ISALPHANUM) return TS_FUNC;  // func
  MATCH_IDENTIFIER;

  // -------- w --------
state_w:
  CHECK_CHAR('h', state_wh);
  MATCH_IDENTIFIER;
state_wh:
  CHECK_CHAR('i', state_whi);
  MATCH_IDENTIFIER;
state_whi:
  CHECK_CHAR('l', state_whil);
  MATCH_IDENTIFIER;
state_whil:
  CHECK_CHAR('e', state_while_end);
  MATCH_IDENTIFIER;
state_while_end:
  if (!ISALPHANUM) return TS_WHILE;  // while
  MATCH_IDENTIFIER;

  // -------- v --------
state_v:
  CHECK_CHAR('a', state_va);
  MATCH_IDENTIFIER;
state_va:
  CHECK_CHAR('r', state_var_end);
  MATCH_IDENTIFIER;
state_var_end:
  if (!ISALPHANUM) return TS_VAR;  // var
  MATCH_IDENTIFIER;

  // -------- p --------
state_p:
  CHECK_CHAR('r', state_pr);
  MATCH_IDENTIFIER;
state_pr:
  CHECK_CHAR('i', state_pri);
  MATCH_IDENTIFIER;
state_pri:
  CHECK_CHAR('n', state_prin);
  MATCH_IDENTIFIER;
state_prin:
  CHECK_CHAR('t', state_print_end);
  MATCH_IDENTIFIER;
state_print_end:
  if (!ISALPHANUM) return TS_PRINT;  // print
  MATCH_IDENTIFIER;

  // -------- s --------
state_s:
  CHECK_CHAR('w', state_sw);
  CHECK_CHAR('t', state_st);
  MATCH_IDENTIFIER;
state_sw:
  CHECK_CHAR('i', state_swi);
  MATCH_IDENTIFIER;
state_swi:
  CHECK_CHAR('t', state_swit);
  MATCH_IDENTIFIER;
state_swit:
  CHECK_CHAR('c', state_switc);
  MATCH_IDENTIFIER;
state_switc:
  CHECK_CHAR('h', state_switch_end);
  MATCH_IDENTIFIER;
state_switch_end:
  if (!ISALPHANUM) return TS_SWITCH;  // switch
  MATCH_IDENTIFIER;
state_st:
  CHECK_CHAR('r', state_str);
  MATCH_IDENTIFIER;
state_str:
  CHECK_CHAR('i', state_stri);
  MATCH_IDENTIFIER;
state_stri:
  CHECK_CHAR('n', state_strin);
  MATCH_IDENTIFIER;
state_strin:
  CHECK_CHAR('g', state_string_end);
  MATCH_IDENTIFIER;
state_string_end:
  if (!ISALPHANUM) return TS_STRING;  // string
  MATCH_IDENTIFIER;

  // -------- c --------
state_c:
  CHECK_CHAR('a', state_ca);
  CHECK_CHAR('o', state_co);
  CHECK_CHAR('h', state_ch);
  MATCH_IDENTIFIER;
state_ca:
  CHECK_CHAR('s', state_cas);
  MATCH_IDENTIFIER;
state_cas:
  CHECK_CHAR('e', state_case_end);
  MATCH_IDENTIFIER;
state_case_end:
  if (!ISALPHANUM) return TS_CASE;  // case
  MATCH_IDENTIFIER;
state_ch:
  CHECK_CHAR('a', state_cha);
  MATCH_IDENTIFIER;
state_cha:
  CHECK_CHAR('r', state_char_end);
  MATCH_IDENTIFIER;
state_char_end:
  if (!ISALPHANUM) return TS_CHAR;  // char
  MATCH_IDENTIFIER;
state_co:
  CHECK_CHAR('n', state_con);
  MATCH_IDENTIFIER;
state_con:
  CHECK_CHAR('t', state_cont);
  MATCH_IDENTIFIER;
state_cont:
  CHECK_CHAR('i', state_conti);
  MATCH_IDENTIFIER;
state_conti:
  CHECK_CHAR('n', state_contin);
  MATCH_IDENTIFIER;
state_contin:
  CHECK_CHAR('u', state_continu);
  MATCH_IDENTIFIER;
state_continu:
  CHECK_CHAR('e', state_continue_end);
  MATCH_IDENTIFIER;
state_continue_end:
  if (!ISALPHANUM) return TS_CONTINUE;  // continue
  MATCH_IDENTIFIER;

  // -------- d --------
state_d:
  CHECK_CHAR('e', state_de);
  MATCH_IDENTIFIER;
state_de:
  CHECK_CHAR('f', state_def);
  MATCH_IDENTIFIER;
state_def:
  CHECK_CHAR('a', state_defa);
  MATCH_IDENTIFIER;
state_defa:
  CHECK_CHAR('u', state_defau);
  MATCH_IDENTIFIER;
state_defau:
  CHECK_CHAR('l', state_defaul);
  MATCH_IDENTIFIER;
state_defaul:
  CHECK_CHAR('t', state_default_end);
  MATCH_IDENTIFIER;
state_default_end:
  if (!ISALPHANUM) return TS_DEFAULT;  // default
  MATCH_IDENTIFIER;

// -------- b --------
state_b:
  CHECK_CHAR('r', state_br);
  CHECK_CHAR('o', state_bo);
  MATCH_IDENTIFIER;
state_br:
  CHECK_CHAR('e', state_bre);
  MATCH_IDENTIFIER;
state_bre:
  CHECK_CHAR('a', state_brea);
  MATCH_IDENTIFIER;
state_brea:
  CHECK_CHAR('k', state_break_end);
  MATCH_IDENTIFIER;
state_break_end:
  if (!ISALPHANUM) return TS_BREAK;  // break
  MATCH_IDENTIFIER;
state_bo:
  CHECK_CHAR('o', state_boo);
  MATCH_IDENTIFIER;
state_boo:
  CHECK_CHAR('l', state_bool_end);
  MATCH_IDENTIFIER;
state_bool_end:
  if (!ISALPHANUM) return TS_BOOL;  // bool
  MATCH_IDENTIFIER;

  // -------- r --------
state_r:
  CHECK_CHAR('e', state_re);
  MATCH_IDENTIFIER;
state_re:
  CHECK_CHAR('t', state_ret);
  MATCH_IDENTIFIER;
state_ret:
  CHECK_CHAR('u', state_retu);
  MATCH_IDENTIFIER;
state_retu:
  CHECK_CHAR('r', state_retur);
  MATCH_IDENTIFIER;
state_retur:
  CHECK_CHAR('n', state_return_end);
  MATCH_IDENTIFIER;
state_return_end:
  if (!ISALPHANUM) return TS_RETURN;  // return
  MATCH_IDENTIFIER;

  // -------- t (true) --------
state_t:
  CHECK_CHAR('r', state_tr);
  MATCH_IDENTIFIER;
state_tr:
  CHECK_CHAR('u', state_tru);
  MATCH_IDENTIFIER;
state_tru:
  CHECK_CHAR('e', state_true_end);
  MATCH_IDENTIFIER;
state_true_end:
  if (!ISALPHANUM) return TS_TRUE;  // true
  MATCH_IDENTIFIER;

  // fallback
  MATCH_IDENTIFIER;
}

// This function recognizes multi-character operators like ++, --, ==, etc.
// Returns the operator type name, or TS_NONE if not recognized.

TokenSpecial dictionary_lookup_symbol(char* lexeme, int* len) {
  (*len) = 0;
  (*len) = 0;
  if (!lexeme || *lexeme == '\0') return TS_NONE;
  (*len)++;
  switch (*lexeme) {
    case '<':
      lexeme++;
      goto state_less;
    case '&':
      lexeme++;
      goto state_amp;
    case '|':
      lexeme++;
      goto state_pipe;
    case '^':
      return TS_POWER;
    case '>':
      lexeme++;
      goto state_greater;
    case '=':
      lexeme++;
      goto state_equal;
    case '+':
      lexeme++;
      goto state_plus;
    case '-':
      lexeme++;
      goto state_minus;
    case '*':
      return TS_MULTIPLY;
    case '/':
      return TS_DIVIDE;
    case '%':
      return TS_MODULO;
    case '!':
      return TS_NOT;
    case '(':
      return TS_L_PAREN;
    case ')':
      return TS_R_PAREN;
    case '{':
      return TS_L_BRACE;
    case '}':
      return TS_R_BRACE;
    case ';':
      return TS_SEMICOLON;
    default:
      MATCH_IDENTIFIER;
  }

  // -------- + --------
state_plus:
  if (*lexeme == '+') {
    lexeme++;
    (*len)++;
    return TS_INCREMENT;  // ++
  }
  return TS_ADD;  // +
  (*len) = 0;
  return TS_NONE;

  // -------- - --------
state_minus:
  if (*lexeme == '-') {
    lexeme++;
    (*len)++;
    return TS_DECREMENT;  // --
  }
  return TS_SUBTRACT;  // -
  (*len) = 0;
  return TS_NONE;

  // -------- / --------
state_slash:
  if (*lexeme == '_') {
    lexeme++;
    (*len)++;
    return TS_DIVIDE_FLOOR;  // /_
  }
  return TS_DIVIDE;  // /
  (*len) = 0;
  return TS_NONE;

  // -------- = --------
state_equal:
  if (*lexeme == '=') {
    lexeme++;
    (*len)++;
    return TS_EQUAL;  // ==
  }
  return TS_ASSIGNMENT;  // =
  (*len) = 0;
  return TS_NONE;

  // -------- < --------
state_less:
  if (*lexeme == '=') {
    lexeme++;
    (*len)++;
    return TS_LESS_EQUAL;  // <=
  }
  return TS_LESS_THAN;  // <
  (*len) = 0;
  return TS_NONE;

  // -------- > --------
state_greater:
  if (*lexeme == '=') {
    lexeme++;
    (*len)++;
    return TS_GREATER_EQUAL;  // >=
  }
  return TS_GREATER_THAN;  // >
  (*len) = 0;
  return TS_NONE;

  // -------- && --------
state_amp:
  if (*lexeme == '&') {
    lexeme++;
    (*len)++;
    return TS_AND;  // &&
  }
  (*len) = 0;
  return TS_NONE;

  // -------- || --------
state_pipe:
  if (*lexeme == '|') {
    lexeme++;
    (*len)++;
    return TS_OR;  // ||
  }
  (*len) = 0;
  return TS_NONE;
}
