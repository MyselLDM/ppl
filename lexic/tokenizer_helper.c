#include "../global/dictionary.h"

// Detects "//..." or "///...///"
int tokenizer_match_comment(char* strptr) {
  // Inline Comment Logic
  if (strptr[0] == '/' && strptr[1] == '/' && strptr[2] != '/') {
    int i = 2;
    while (strptr[i] != '\0' && strptr[i] != '\n') i++;
    return i;
  }

  // Block Comment Logic
  if (strptr[0] == '/' && strptr[1] == '/' && strptr[2] == '/') {
    int i = 3;
    while (
        !(strptr[i] == '/' && strptr[i + 1] == '/' && strptr[i + 2] == '/') &&
        strptr[i] != '\0')
      i++;
    return (strptr[i] == '\0') ? 0 : i + 3;
  }

  // No Comment
  return 0;
}

// Ony returns true if the current string is ' and the one after the character
// is '
int tokenizer_match_char(char* strptr) {
  if (strptr[0] == '\'' && strptr[2] == '\'' && strptr[1] != '\'') return 3;
  return 0;
}

int tokenizer_match_string(char* strptr) {
  if (strptr[0] != '"') return 0;
  int i = 1;
  while (strptr[i] != '"' && strptr[i] != '\0' && strptr[i] != '\n') i++;
  if (strptr[i] == '"') return i + 1;
  return 0;  // unclosed string
}

int tokenizer_match_float(char* strptr) {
  int i = 0;
  if (strptr[i] == '-') i++;

  int start_digits = i;
  // digits before dot
  while (strptr[i] >= '0' && strptr[i] <= '9') i++;

  if (i == start_digits) return 0;  // no digits before dot

  if (strptr[i] != '.') return 0;  // must have a dot
  i++;

  int after_dot_start = i;
  // digits after dot
  while (strptr[i] >= '0' && strptr[i] <= '9') i++;

  if (i == after_dot_start) return 0;  // no digits after dot

  // Check terminator: end of string or non-alphanumeric
  char next = strptr[i];
  if ((next >= '0' && next <= '9') || (next >= 'A' && next <= 'Z') ||
      (next >= 'a' && next <= 'z') || next == '_') {
    return 0;  // invalid if letter, digit, or underscore follows
  }

  return i;
}

int tokenizer_match_integer(char* strptr) {
  int i = 0;
  if (strptr[i] == '-') i++;

  int start_digits = i;
  while (strptr[i] >= '0' && strptr[i] <= '9') i++;

  if (i == start_digits) return 0;  // no digits

  // Check terminator: end of string or non-alphanumeric
  char next = strptr[i];
  if ((next >= '0' && next <= '9') || (next >= 'A' && next <= 'Z') ||
      (next >= 'a' && next <= 'z') || next == '_') {
    return 0;  // invalid if letter, digit, or underscore follows
  }

  return i;
}

int tokenizer_match_delimiter(char* strptr) {
  const char* delsymbols = "();{}";
  for (int i = 0; delsymbols[i] != '\0'; i++) {
    if (strptr[0] == delsymbols[i]) return 1;
  }
  return 0;
}

/* Generic symbol matcher */
int tokenizer_match_symbol(const char* strptr, const char* symbols[][2],
                           int count) {
  for (int i = 0; i < count; i++) {
    const char* op = symbols[i][0];
    int j = 0;
    while (op[j] && strptr[j] && op[j] == strptr[j]) j++;
    if (op[j] == '\0') return (int)j;  // full match length
  }
  return 0;
}

int tokenizer_match_operator(const char* strptr) {
  if (strptr[0] == '=' && strptr[1] == '=') return 2;
  if (strptr[0] == '&' && strptr[1] == '&') return 2;
  if (strptr[0] == '|' && strptr[1] == '|') return 2;

  // Arithmetic
  const char* ops = "+-*/%^<>!=";
  if (strptr[0] == '%' && strptr[1] == '%') return 2;
  for (int i = 0; ops[i] != '\0'; i++) {
    if (strptr[0] == ops[i]) {
      if (strptr[1] == '=') return 2;
      return 1;
    }
  }

  return 0;
}

int tokenizer_match_text(char* strptr) {
  if (!((strptr[0] >= 'a' && strptr[0] <= 'z') ||
        (strptr[0] >= 'A' && strptr[0] <= 'Z') || strptr[0] == '_'))
    return 0;

  int i = 1;
  while ((strptr[i] >= 'a' && strptr[i] <= 'z') ||
         (strptr[i] >= 'A' && strptr[i] <= 'Z') ||
         (strptr[i] >= '0' && strptr[i] <= '9') || strptr[i] == '_')
    i++;
  return i;
}

int tokenizer_match_invalid(char* strptr) {
  int i = 0;
  while (strptr[i] != '\0' && strptr[i] != ' ' && strptr[i] != '\t' &&
         strptr[i] != '\n' && tokenizer_match_delimiter(&strptr[i]) == 0)
    i++;
  return i;
}
