#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

#define CHECK_CHAR(c, next_state) \
  do {                            \
    if (*lexeme == c) {           \
      lexeme++;                   \
      goto next_state;            \
    }                             \
  } while (0)

const char* dictionary_lookup_text(char* lexeme) {
  if (!lexeme || *lexeme == '\0') return "identifier";

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
      return "identifier";
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
  return "identifier";
state_if_end:
  if (*lexeme == '\0') return "keyword";  // if
  return "identifier";
state_int:
  if (*lexeme == '\0') return "noise";  // int
  return "identifier";

  // -------- e --------
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
  if (*lexeme == '\0') return "keyword";  // else
  return "identifier";

  // -------- f --------
state_f:
  CHECK_CHAR('o', state_fo);  // for
  CHECK_CHAR('l', state_fl);  // float or false
  return "identifier";

  // for
state_fo:
  CHECK_CHAR('r', state_for_end);
  return "identifier";
state_for_end:
  if (*lexeme == '\0') return "keyword";  // for
  return "identifier";

  // handle both "float" and "false"
state_fl:
  CHECK_CHAR('o', state_flo);  // float
  CHECK_CHAR('a', state_fa);   // false
  return "identifier";

  // float
state_flo:
  CHECK_CHAR('a', state_floa);
  return "identifier";
state_floa:
  CHECK_CHAR('t', state_float_end);
  return "identifier";
state_float_end:
  if (*lexeme == '\0') return "noise";  // float
  return "identifier";

  // false
state_fa:
  CHECK_CHAR('l', state_fal);
  return "identifier";
state_fal:
  CHECK_CHAR('s', state_fals);
  return "identifier";
state_fals:
  CHECK_CHAR('e', state_false_end);
  return "identifier";
state_false_end:
  if (*lexeme == '\0') return "constant";  // false
  return "identifier";

  // -------- w --------
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
  if (*lexeme == '\0') return "keyword";  // while
  return "identifier";

  // -------- v --------
state_v:
  CHECK_CHAR('a', state_va);
  return "identifier";
state_va:
  CHECK_CHAR('r', state_var_end);
  return "identifier";
state_var_end:
  if (*lexeme == '\0') return "keyword";  // var
  return "identifier";

  // -------- p --------
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
  if (*lexeme == '\0') return "keyword";  // print
  return "identifier";

  // -------- s --------
state_s:
  CHECK_CHAR('w', state_sw);
  CHECK_CHAR('t', state_st);
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
  if (*lexeme == '\0') return "reserved";  // switch
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
  if (*lexeme == '\0') return "noise";  // string
  return "identifier";

  // -------- c --------
state_c:
  CHECK_CHAR('a', state_ca);
  CHECK_CHAR('o', state_co);
  return "identifier";
state_ca:
  CHECK_CHAR('s', state_cas);
  CHECK_CHAR('h', state_char_end);
  return "identifier";
state_cas:
  CHECK_CHAR('e', state_case_end);
  return "identifier";
state_case_end:
  if (*lexeme == '\0') return "reserved";  // case
  return "identifier";
state_char_end:
  if (*lexeme == '\0') return "noise";  // char
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
  if (*lexeme == '\0') return "reserved";  // continue
  return "identifier";

  // -------- d --------
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
  if (*lexeme == '\0') return "reserved";  // default
  return "identifier";

  // -------- b --------
state_b:
  CHECK_CHAR('r', state_br);
  CHECK_CHAR('o', state_bo);
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
  if (*lexeme == '\0') return "reserved";  // break
  return "identifier";
state_bo:
  CHECK_CHAR('o', state_boo);
  return "identifier";
state_boo:
  CHECK_CHAR('l', state_bool_end);
  return "identifier";
state_bool_end:
  if (*lexeme == '\0') return "noise";  // bool
  return "identifier";

  // -------- r --------
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
  if (*lexeme == '\0') return "reserved";  // return
  return "identifier";

  // -------- t (true) --------
state_t:
  CHECK_CHAR('r', state_tr);
  return "identifier";
state_tr:
  CHECK_CHAR('u', state_tru);
  return "identifier";
state_tru:
  CHECK_CHAR('e', state_true_end);
  return "identifier";
state_true_end:
  if (*lexeme == '\0') return "constant";  // true
  return "identifier";

  // fallback
  return "identifier";
}
