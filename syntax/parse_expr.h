#ifndef PARSE_EXPR_H
#define PARSE_EXPR_H

#include "ast.h"
#include "parse_error.h"

ASTNode* parse_expression(const Tokens* tokens, size_t* index);

#endif