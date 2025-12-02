#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global/debug_print.h"
// #include "legacy_code/tokenizer.h"
#include "lexic/scanner.h"
#include "lexic/tokenizer.h"
#include "syntax/astprint.h"
#include "syntax/bxparser.h"

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

  DEBUG_PRINT("[!!MAIN!!] Successfully parsed '%s'\n", FILE_NAME);
  DEBUG_PRINT("[!!MAIN!!] Starting tokenization of '%s'\n", FILE_NAME);

  Tokens tokens = tokenizer_token_scan_manual(fstr);
  //  token_optimize(&tokens);

  DEBUG_PRINT("[!!MAIN!!] Successfully tokenized '%s'\n", FILE_NAME);

  // for (size_t i = 0; i < tokens.length; i++) {
  //   Token* t = &tokens.token[i];
  //   DEBUG_PRINT(
  //       "Line %d Offset %d Lexeme: %s Token Type: %s Token Special: %s \n",
  //       t->line, t->offset, t->lexeme, tt2str(t->token_type),
  //       ts2str(t->token_type_special));
  // }

  ASTNode* ast_root = parse_tokens(&tokens);

  ast_print(ast_root, 0);

  debug_close();

  return 0;
}