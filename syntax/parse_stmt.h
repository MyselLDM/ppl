#ifndef PARSE_STMT_H
#define PARSE_STMT_H

#include "ast.h"
#include "parse_error.h"
ASTNode* parse_assignment(const Tokens* tokens, size_t* index);
ASTNode* parse_print(const Tokens* tokens, size_t* index);
ASTNode* parse_if(const Tokens* tokens, size_t* index);
ASTNode* parse_while(const Tokens* tokens, size_t* index);
ASTNode* parse_write(const Tokens* tokens, size_t* index);
ASTNode* parse_for(const Tokens* tokens, size_t* index);
ASTNode* parse_block(const Tokens* tokens, size_t* index);

#endif