#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global/debug_print.h"
#include "lexical_analyzer/scanner.h"
#include "lexical_analyzer/token.h"
#include "lexical_analyzer/tokenizer.h"

int main(int argc, char* argv[]) {
  // CLI Argument Checking
  if (argc < 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  debug = 1;
  debug_init("debug.log");
  DEBUG_PRINT("%s: Successfully parsed CLI arguments\n", __func__);

  // Parses the file returns the entire file as a string
  char* FILE_NAME = argv[1];
  char* fstr = parser_scan_file(FILE_NAME);

  DEBUG_PRINT(
      "============================================\n%s: Successfully parsed "
      "file\n============================================\n",
      __func__);

  // Tokenizes the file input and stores it in a struct array
  Tokens tokens = tokenizer_token_scan(fstr);

  DEBUG_PRINT(
      "============================================\n%s: Successfully parsed "
      "tokens\n============================================\n",
      __func__);

  debug_close();

  return 0;
}
