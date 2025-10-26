#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string_builder.h"

// Common String Builder for creating tokens for the strings
void string_builder_init(StringBuilder* sb) {
  sb->str = NULL;
  sb->capacity = 0;
  sb->len = 0;
}

void string_builder_free(StringBuilder* sb) {
  free(sb->str);
  sb->str = NULL;
  sb->capacity = 0;
  sb->len = 0;
}

void string_builder_append(StringBuilder* sb, char c) {
  if (sb->len == sb->capacity) {
    sb->capacity *= 2;
    sb->str = realloc(sb->str, sb->capacity);
  }
  sb->str[sb->len++] = c;
}

void string_builder_print(StringBuilder* sb) {
  printf("%s\n", sb->str);
}

char* string_builder_get(StringBuilder* sb) {
  return sb->str;
}
