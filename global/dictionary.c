#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>

// Automata Macro for checking the next character
#define CHECK_CHAR(c, next_state) \
  do {                            \
    if (*lexeme == c) {           \
      lexeme++;                   \
      goto next_state;            \
    }                             \
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

// Lookup Table for Token Type from Token Special
TokenType token_type_lookup(TokenSpecial ts) {
  if (TS_NONE == ts) return T_INVALID;

  if (TS_IF <= ts && ts <= TS_PRINT) return T_KEYWORD;
  if (TS_SWITCH <= ts && ts <= TS_CONTINUE) return T_RESERVED;
  if (TS_INT <= ts && ts <= TS_STRING) return T_NOISE;
  if (TS_TRUE <= ts && ts <= TS_FLOAT_LITERAL) return T_CONSTANT;
  if (TS_SEMICOLON <= ts && ts <= TS_GREATER_THAN) return T_DELIMITER;
  if (TS_IDENTIFIER == ts) return T_IDENTIFIER;
  if (TS_COMMENT_BLOCK == ts || ts == TS_COMMENT_LINE) return T_COMMENT;

  return T_UNKNOWN;
}

TokenSpecial dictionary_lookup_text(char* lexeme) {
  if (!lexeme || *lexeme == '\0') return TS_IDENTIFIER;

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
      return TS_IDENTIFIER;
  }

  // -------- i --------
state_i:
  if (*lexeme == 'f') {
    lexeme++;
    goto state_if_end;
  }
  if (*lexeme == 'n') {
    lexeme++;
    goto state_int;
  }
  return TS_IDENTIFIER;
state_if_end:
  if (*lexeme == '\0') return TS_IF;  // if
  return TS_IDENTIFIER;
state_int:
  if (*lexeme == '\0') return TS_INT;  // int
  return TS_IDENTIFIER;

  // -------- e --------
state_e:
  CHECK_CHAR('l', state_el);
  return TS_IDENTIFIER;
state_el:
  CHECK_CHAR('s', state_els);
  return TS_IDENTIFIER;
state_els:
  CHECK_CHAR('e', state_else_end);
  return TS_IDENTIFIER;
state_else_end:
  if (*lexeme == '\0') return TS_ELSE;  // else
  return TS_IDENTIFIER;

  // -------- f --------
state_f:
  CHECK_CHAR('o', state_fo);  // for
  CHECK_CHAR('l', state_fl);  // float
  CHECK_CHAR('a', state_fa);  // false
  CHECK_CHAR('u', state_fu);  // func
  return TS_IDENTIFIER;

  // for
state_fo:
  CHECK_CHAR('r', state_for_end);
  return TS_IDENTIFIER;
state_for_end:
  if (*lexeme == '\0') return TS_FOR;  // for
  return TS_IDENTIFIER;

  // handle both "float"
state_fl:
  CHECK_CHAR('o', state_flo);  // float
  return TS_IDENTIFIER;
  // float
state_flo:
  CHECK_CHAR('a', state_floa);
  return TS_IDENTIFIER;
state_floa:
  CHECK_CHAR('t', state_float_end);
  return TS_IDENTIFIER;
state_float_end:
  if (*lexeme == '\0') return TS_FLOAT;  // float
  return TS_IDENTIFIER;

  // false
state_fa:
  CHECK_CHAR('l', state_fal);
  return TS_IDENTIFIER;
state_fal:
  CHECK_CHAR('s', state_fals);
  return TS_IDENTIFIER;
state_fals:
  CHECK_CHAR('e', state_false_end);
  return TS_IDENTIFIER;
state_false_end:
  if (*lexeme == '\0') return TS_FALSE;  // false
  return TS_IDENTIFIER;

state_fu:
  CHECK_CHAR('n', state_fun);
  return TS_IDENTIFIER;
state_fun:
  CHECK_CHAR('c', state_func_end);
  return TS_IDENTIFIER;
state_func_end:
  if (*lexeme == '\0') return TS_FUNC;  // func
  return TS_IDENTIFIER;

  // -------- w --------
state_w:
  CHECK_CHAR('h', state_wh);
  return TS_IDENTIFIER;
state_wh:
  CHECK_CHAR('i', state_whi);
  return TS_IDENTIFIER;
state_whi:
  CHECK_CHAR('l', state_whil);
  return TS_IDENTIFIER;
state_whil:
  CHECK_CHAR('e', state_while_end);
  return TS_IDENTIFIER;
state_while_end:
  if (*lexeme == '\0') return TS_WHILE;  // while
  return TS_IDENTIFIER;

  // -------- v --------
state_v:
  CHECK_CHAR('a', state_va);
  return TS_IDENTIFIER;
state_va:
  CHECK_CHAR('r', state_var_end);
  return TS_IDENTIFIER;
state_var_end:
  if (*lexeme == '\0') return TS_VAR;  // var
  return TS_IDENTIFIER;

  // -------- p --------
state_p:
  CHECK_CHAR('r', state_pr);
  return TS_IDENTIFIER;
state_pr:
  CHECK_CHAR('i', state_pri);
  return TS_IDENTIFIER;
state_pri:
  CHECK_CHAR('n', state_prin);
  return TS_IDENTIFIER;
state_prin:
  CHECK_CHAR('t', state_print_end);
  return TS_IDENTIFIER;
state_print_end:
  if (*lexeme == '\0') return TS_PRINT;  // print
  return TS_IDENTIFIER;

  // -------- s --------
state_s:
  CHECK_CHAR('w', state_sw);
  CHECK_CHAR('t', state_st);
  return TS_IDENTIFIER;
state_sw:
  CHECK_CHAR('i', state_swi);
  return TS_IDENTIFIER;
state_swi:
  CHECK_CHAR('t', state_swit);
  return TS_IDENTIFIER;
state_swit:
  CHECK_CHAR('c', state_switc);
  return TS_IDENTIFIER;
state_switc:
  CHECK_CHAR('h', state_switch_end);
  return TS_IDENTIFIER;
state_switch_end:
  if (*lexeme == '\0') return TS_SWITCH;  // switch
  return TS_IDENTIFIER;
state_st:
  CHECK_CHAR('r', state_str);
  return TS_IDENTIFIER;
state_str:
  CHECK_CHAR('i', state_stri);
  return TS_IDENTIFIER;
state_stri:
  CHECK_CHAR('n', state_strin);
  return TS_IDENTIFIER;
state_strin:
  CHECK_CHAR('g', state_string_end);
  return TS_IDENTIFIER;
state_string_end:
  if (*lexeme == '\0') return TS_STRING;  // string
  return TS_IDENTIFIER;

  // -------- c --------
state_c:
  CHECK_CHAR('a', state_ca);
  CHECK_CHAR('o', state_co);
  CHECK_CHAR('h', state_ch);
  return TS_IDENTIFIER;
state_ca:
  CHECK_CHAR('s', state_cas);
  return TS_IDENTIFIER;
state_cas:
  CHECK_CHAR('e', state_case_end);
  return TS_IDENTIFIER;
state_case_end:
  if (*lexeme == '\0') return TS_CASE;  // case
  return TS_IDENTIFIER;
state_ch:
  CHECK_CHAR('a', state_cha);
  return TS_IDENTIFIER;
state_cha:
  CHECK_CHAR('r', state_char_end);
  return TS_IDENTIFIER;
state_char_end:
  if (*lexeme == '\0') return TS_CHAR;  // char
  return TS_IDENTIFIER;
state_co:
  CHECK_CHAR('n', state_con);
  return TS_IDENTIFIER;
state_con:
  CHECK_CHAR('t', state_cont);
  return TS_IDENTIFIER;
state_cont:
  CHECK_CHAR('i', state_conti);
  return TS_IDENTIFIER;
state_conti:
  CHECK_CHAR('n', state_contin);
  return TS_IDENTIFIER;
state_contin:
  CHECK_CHAR('u', state_continu);
  return TS_IDENTIFIER;
state_continu:
  CHECK_CHAR('e', state_continue_end);
  return TS_IDENTIFIER;
state_continue_end:
  if (*lexeme == '\0') return TS_CONTINUE;  // continue
  return TS_IDENTIFIER;

  // -------- d --------
state_d:
  CHECK_CHAR('e', state_de);
  return TS_IDENTIFIER;
state_de:
  CHECK_CHAR('f', state_def);
  return TS_IDENTIFIER;
state_def:
  CHECK_CHAR('a', state_defa);
  return TS_IDENTIFIER;
state_defa:
  CHECK_CHAR('u', state_defau);
  return TS_IDENTIFIER;
state_defau:
  CHECK_CHAR('l', state_defaul);
  return TS_IDENTIFIER;
state_defaul:
  CHECK_CHAR('t', state_default_end);
  return TS_IDENTIFIER;
state_default_end:
  if (*lexeme == '\0') return TS_DEFAULT;  // default
  return TS_IDENTIFIER;

// -------- b --------
state_b:
  CHECK_CHAR('r', state_br);
  CHECK_CHAR('o', state_bo);
  return TS_IDENTIFIER;
state_br:
  CHECK_CHAR('e', state_bre);
  return TS_IDENTIFIER;
state_bre:
  CHECK_CHAR('a', state_brea);
  return TS_IDENTIFIER;
state_brea:
  CHECK_CHAR('k', state_break_end);
  return TS_IDENTIFIER;
state_break_end:
  if (*lexeme == '\0') return TS_BREAK;  // break
  return TS_IDENTIFIER;
state_bo:
  CHECK_CHAR('o', state_boo);
  return TS_IDENTIFIER;
state_boo:
  CHECK_CHAR('l', state_bool_end);
  return TS_IDENTIFIER;
state_bool_end:
  if (*lexeme == '\0') return TS_BOOL;  // bool
  return TS_IDENTIFIER;

  // -------- r --------
state_r:
  CHECK_CHAR('e', state_re);
  return TS_IDENTIFIER;
state_re:
  CHECK_CHAR('t', state_ret);
  return TS_IDENTIFIER;
state_ret:
  CHECK_CHAR('u', state_retu);
  return TS_IDENTIFIER;
state_retu:
  CHECK_CHAR('r', state_retur);
  return TS_IDENTIFIER;
state_retur:
  CHECK_CHAR('n', state_return_end);
  return TS_IDENTIFIER;
state_return_end:
  if (*lexeme == '\0') return TS_RETURN;  // return
  return TS_IDENTIFIER;

  // -------- t (true) --------
state_t:
  CHECK_CHAR('r', state_tr);
  return TS_IDENTIFIER;
state_tr:
  CHECK_CHAR('u', state_tru);
  return TS_IDENTIFIER;
state_tru:
  CHECK_CHAR('e', state_true_end);
  return TS_IDENTIFIER;
state_true_end:
  if (*lexeme == '\0') return TS_TRUE;  // true
  return TS_IDENTIFIER;

  // fallback
  return TS_IDENTIFIER;
}

// This function recognizes multi-character operators like ++, --, ==, etc.
// Returns the operator type name, or TS_NONE if not recognized.
TokenSpecial dictionary_lookup_symbol(char* lexeme) {
  if (!lexeme || *lexeme == '\0') return TS_NONE;

  switch (*lexeme) {
    case '+':
      lexeme++;
      goto state_plus;
    case '-':
      lexeme++;
      goto state_minus;
    case '*':
      lexeme++;
      goto state_star;
    case '/':
      lexeme++;
      goto state_slash;
    case '%':
      lexeme++;
      goto state_percent;
    case '=':
      lexeme++;
      goto state_equal;
    case '!':
      lexeme++;
      goto state_exclam;
    case '<':
      lexeme++;
      goto state_less;
    case '>':
      lexeme++;
      goto state_greater;
    case '&':
      lexeme++;
      goto state_amp;
    case '|':
      lexeme++;
      goto state_pipe;
    case '^':
      lexeme++;
      goto state_caret;
    default:
      return TS_NONE;
  }

  // -------- + --------
state_plus:
  if (*lexeme == '+') {
    lexeme++;
    if (*lexeme == '\0') return TS_INCREMENT;  // ++
  }
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return TS_ADD_ASSIGNMENT;  // +=
  }
  if (*lexeme == '\0') return TS_ADD;  // +
  return TS_NONE;

  // -------- - --------
state_minus:
  if (*lexeme == '-') {
    lexeme++;
    if (*lexeme == '\0') return TS_DECREMENT;  // --
  }
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return TS_SUBTRACT_ASSIGNMENT;  // -=
  }
  if (*lexeme == '\0') return TS_SUBTRACT;  // -
  return TS_NONE;

  // -------- * --------
state_star:
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return TS_MULTIPLY_ASSIGNMENT;  // *=
  }
  if (*lexeme == '\0') return TS_MULTIPLY;  // *
  return TS_NONE;

  // -------- / --------
state_slash:
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return TS_DIVIDE_ASSIGNMENT;  // /=
  }
  if (*lexeme == '\0') return TS_DIVIDE;  // /
  return TS_NONE;

  // -------- % --------
state_percent:
  if (*lexeme == '%') {
    lexeme++;
    if (*lexeme == '\0') return TS_DIVIDE_FLOOR;  // %%
  }
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return TS_MODULO_ASSIGNMENT;  // %=
  }
  if (*lexeme == '\0') return TS_MODULO;  // %
  return TS_NONE;

  // -------- = --------
state_equal:
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return TS_EQUAL;  // ==
  }
  if (*lexeme == '\0') return TS_ASSIGNMENT;  // =
  return TS_NONE;

  // -------- ! --------
state_exclam:
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return TS_NOT_EQUAL;  // !=
  }
  if (*lexeme == '\0') return TS_NOT;  // !
  return TS_NONE;

  // -------- < --------
state_less:
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return TS_LESS_EQUAL;  // <=
  }
  if (*lexeme == '\0') return TS_LESS_THAN;  // <
  return TS_NONE;

  // -------- > --------
state_greater:
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return TS_GREATER_EQUAL;  // >=
  }
  if (*lexeme == '\0') return TS_GREATER_THAN;  // >
  return TS_NONE;

  // -------- && --------
state_amp:
  if (*lexeme == '&') {
    lexeme++;
    if (*lexeme == '\0') return TS_AND;  // &&
  }
  return TS_NONE;

  // -------- || --------
state_pipe:
  if (*lexeme == '|') {
    lexeme++;
    if (*lexeme == '\0') return TS_OR;  // ||
  }
  return TS_NONE;

  // -------- ^ --------
state_caret:
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return TS_POWER_ASSIGNMENT;  // ^=
  }
  if (*lexeme == '\0') return TS_POWER;  // ^
  return TS_NONE;

  return TS_NONE;
}
