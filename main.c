#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global/debug_print.h"
// #include "legacy_code/tokenizer.h"
#include "lexic/scanner.h"
#include "lexic/tokenizer_manual.h"
int main(int argc, char* argv[]) {
  // CLI Argument Checking
  if (argc < 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  // Parses the file returns the entire file as a string
  char* FILE_NAME = argv[1];

  // Initializes the debug system
  debug_init("debug.log");
  DEBUG_PRINT("%s: Successfully parsed CLI arguments\n", __func__);

  char* fstr = parser_scan_file(FILE_NAME);
  // char* fstr2 = fstr;

  DEBUG_PRINT("[!!MAIN!!] Successfully parsed '%s'\n", FILE_NAME);
  DEBUG_PRINT("[!!MAIN!!] Starting tokenization of '%s'\n", FILE_NAME);

  // Tokenizes the file input and stores it in a struct array
  Tokens tokens = tokenizer_token_scan_manual(fstr);
  // DEBUG_PRINT("[!!MAIN!!] Starting LEGACY tokenization of '%s'\n",
  // FILE_NAME);
  // Tokens tokensold = tokenizer_token_scan(fstr);

  // Tokenizes the file input and stores it in a struct array
  // tokenizer_token_scan_manual(fstr2);

  DEBUG_PRINT("[!!MAIN!!] Successfully tokenized '%s'\n", FILE_NAME);

  // TODO: Create the AST from the tokenized file
  // AST ast = ast_create(tokens);

  // TODO: Analyze the semantics of the AST

  debug_close();

  return 0;
}
