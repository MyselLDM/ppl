#ifndef INTERPRETER_STRUCT_H
#define INTERPRETER_STRUCT_H

#include "../syntax/ast.h"

void variable_push(ASTNode* node);
void variable_pop(ASTNode* node);
ASTNode* variable_scope_push();
ASTNode* variable_scope_pop();

#endif