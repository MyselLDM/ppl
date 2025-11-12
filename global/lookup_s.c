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

// This function recognizes multi-character operators like ++, --, ==, etc.
// Returns the operator type name, or "" if not recognized.
const char* dictionary_manual_symbol_lookup(char* lexeme) {
  if (!lexeme || *lexeme == '\0') return "";

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
      return "";
  }

  // -------- + --------
state_plus:
  if (*lexeme == '+') {
    lexeme++;
    if (*lexeme == '\0') return "increment";  // ++
  }
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return "add_assign";  // +=
  }
  if (*lexeme == '\0') return "add";  // +
  return "";

  // -------- - --------
state_minus:
  if (*lexeme == '-') {
    lexeme++;
    if (*lexeme == '\0') return "decrement";  // --
  }
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return "subtract_assign";  // -=
  }
  if (*lexeme == '\0') return "subtract";  // -
  return "";

  // -------- * --------
state_star:
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return "multiply_assign";  // *=
  }
  if (*lexeme == '\0') return "multiply";  // *
  return "";

  // -------- / --------
state_slash:
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return "divide_assign";  // /=
  }
  if (*lexeme == '\0') return "divide";  // /
  return "";

  // -------- % --------
state_percent:
  if (*lexeme == '%') {
    lexeme++;
    if (*lexeme == '\0') return "divide_floor";  // %%
  }
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return "mod_assign";  // %=
  }
  if (*lexeme == '\0') return "modulo";  // %
  return "";

  // -------- = --------
state_equal:
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return "equal";  // ==
  }
  if (*lexeme == '\0') return "assignment";  // =
  return "";

  // -------- ! --------
state_exclam:
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return "not_equal";  // !=
  }
  if (*lexeme == '\0') return "not";  // !
  return "";

  // -------- < --------
state_less:
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return "less_equal";  // <=
  }
  if (*lexeme == '\0') return "less_than";  // <
  return "";

  // -------- > --------
state_greater:
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return "greater_equal";  // >=
  }
  if (*lexeme == '\0') return "greater_than";  // >
  return "";

  // -------- && --------
state_amp:
  if (*lexeme == '&') {
    lexeme++;
    if (*lexeme == '\0') return "and";  // &&
  }
  return "";

  // -------- || --------
state_pipe:
  if (*lexeme == '|') {
    lexeme++;
    if (*lexeme == '\0') return "or";  // ||
  }
  return "";

  // -------- ^ --------
state_caret:
  if (*lexeme == '=') {
    lexeme++;
    if (*lexeme == '\0') return "power_assign";  // ^=
  }
  if (*lexeme == '\0') return "power";  // ^
  return "";

  return "";
}
