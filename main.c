#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils/parser.h"
#include "utils/tokenizer.h"

int main() {
  char *fstr = parser_scan_file("example.bx");

  tokenizer_parse_tokens(fstr);


  return 0;
}