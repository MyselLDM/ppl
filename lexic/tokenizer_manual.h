#ifndef TOKENIZER_MANUAL_H
#define TOKENIZER_MANUAL_H

#include "token.h"

char* tokenizer_parse_lexeme(char* strptr, char** token_type);
Tokens tokenizer_token_scan_manual(char* strptr);

#endif