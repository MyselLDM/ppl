#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexical_analyzer/scanner.h"
#include "lexical_analyzer/token.h"
#include "lexical_analyzer/tokenizer.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  char* FILE_NAME = argv[1];
  char* fstr = parser_scan_file(FILE_NAME);

  Tokens tokens = tokenizer_token_scan(fstr);

  return 0;
}