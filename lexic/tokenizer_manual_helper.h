#ifndef TOKENIZER_MANUAL_HELPER_H
#define TOKENIZER_MANUAL_HELPER_H

int tokenizer_match_comment(char* strptr);
int tokenizer_match_char(char* strptr);
int tokenizer_match_string(char* strptr);
int tokenizer_match_number(char* strptr);
int tokenizer_match_delimiter(char* strptr);
int tokenizer_match_operator(char* strptr);
int tokenizer_match_text(char* strptr);
int tokenizer_match_invalid(char* strptr);

#endif