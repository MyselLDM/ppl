#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

char* tokenizer_parse_tokens(char* filename) {
  char* strptr = filename;
  
  while(*strptr != '\0') {
    printf("(%c)", *strptr);
    strptr++;
  }

  return NULL;
}

