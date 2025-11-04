#include "tokenizer_helper.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../global/debug_print.h"
#include "token.h"
#include "tokenizer.h"

int peek_char(char* strptr) {
  char* tempchar = strptr;
  int len = 0;
  if (*tempchar == '\'') {
    tempchar++;
  }

  if (*tempchar == '\'') {
    return -1;
  } else {
    tempchar++;
  }

  if (*tempchar == '\'') {
    return 3;
  } else {
    return -1;
  }
}