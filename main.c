#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1
#define NO_DEBUG 0

#include "lexical_analyzer/scanner.h"
#include "lexical_analyzer/token.h"
#include "lexical_analyzer/tokenizer.h"

int main(int argc, char* argv[]) {
  // Argument Checking
  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  // Parses the file returns the entire file as a string
  char* FILE_NAME = argv[1];
  char* fstr = parser_scan_file(FILE_NAME);

  // Tokenizes the input and stores it in a struct
  Tokens tokens = tokenizer_token_scan(fstr, NO_DEBUG);

  return 0;
}