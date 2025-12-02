#ifndef PARSE_STMT_H
#define PARSE_STMT_H

#include "ast.h"

void parse_error(const char* message, size_t line, size_t offset);

ASTNode* parse_assignment(const Tokens* tokens, size_t* index);
ASTNode* parse_print(const Tokens* tokens, size_t* index);
ASTNode* parse_if(const Tokens* tokens, size_t* index);
ASTNode* parse_while(const Tokens* tokens, size_t* index);
ASTNode* parse_for(const Tokens* tokens, size_t* index);

#endif