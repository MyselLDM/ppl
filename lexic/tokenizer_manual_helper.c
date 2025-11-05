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
  if (strptr[0] == '\'' && strptr[2] == '\'') return 3;
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
  int has_digit = 0, has_dot = 0;

  while (strptr[i] >= '0' && strptr[i] <= '9') {
    i++;
    has_digit = 1;
  }

  if (strptr[i] == '.') {
    has_dot = 1;
    i++;
    while (strptr[i] >= '0' && strptr[i] <= '9') i++;
  }

  return has_digit ? i : 0;
}

int tokenizer_match_integer(char* strptr) {
  int i = 0;
  if (strptr[i] == '-') i++;
  int has_digit = 0, has_dot = 0;

  while (strptr[i] >= '0' && strptr[i] <= '9') {
    i++;
    has_digit = 1;
  }

  return has_digit ? i : 0;
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

/* Category-specific matchers */
int tokenizer_match_operator_arithmetic(const char* strptr) {
  return tokenizer_match_symbol(
      strptr, CONST_symbol_arithmetic,
      sizeof(CONST_symbol_arithmetic) / sizeof(CONST_symbol_arithmetic[0]));
}

int tokenizer_match_operator_logical(const char* strptr) {
  return tokenizer_match_symbol(
      strptr, CONST_symbol_logical,
      sizeof(CONST_symbol_logical) / sizeof(CONST_symbol_logical[0]));
}

int tokenizer_match_operator(const char* strptr) {
  int len = tokenizer_match_operator_logical(strptr);
  if (len) return len;

  len = tokenizer_match_operator_arithmetic(strptr);
  if (len) return len;

  return 0;  // explicit, same logic, more readable to new maintainers
}

int tokenizer_match_boolean(const char* strptr) {
  // Returns the length of the token, 0 if ineligible
  if (strptr[0] == 't' && strptr[1] == 'r' && strptr[2] == 'u' &&
      strptr[3] == 'e')
    return 4;
  if (strptr[0] == 'f' && strptr[1] == 'a' && strptr[2] == 'l' &&
      strptr[3] == 's' && strptr[4] == 'e')
    return 5;
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
