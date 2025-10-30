#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexical_analyzer/parser.h"
#include "lexical_analyzer/tokenizer.h"

int main() {
  char* fstr = parser_scan_file("example.bx");

  tokenizer_token_scan(fstr);

  return 0;
}