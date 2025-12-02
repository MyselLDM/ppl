#include "parse_stmt.h"

#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"
#include "ast.h"
#include "parse_expr.h"
#include "putils.h"

ASTNode* parse_var(const Tokens* tokens, size_t* index) {
  (*index)++;

  // Noise Word
  if (CURRENT_TOKEN.token_type == T_NOISE) {
    (*index)++;
  }

  if (CURRENT_TOKEN.token_type != T_IDENTIFIER) {
    PARSE_ERROR("Expected variable name");
  }

  Token* identifier = &CURRENT_TOKEN;

  (*index)++;

  if (CURRENT_TOKEN.token_type_special != TS_ASSIGNMENT) {
    PARSE_ERROR("Expected \"=\"");
  }

  (*index)++;

  ASTNode* node_as = ast_create_node(AST_STMT_ASSIGN, NULL);
  ASTNode* node_ident = ast_create_node(AST_IDENTIFIER, identifier);
  ASTNode* expr_node = parse_expression(tokens, index);

  ast_add_child(node_as, node_ident);
  ast_add_child(node_as, expr_node);
  return node_as;
}

ASTNode* parse_print(const Tokens* tokens, size_t* index) {
  // TODO: Implement print parsing
  return NULL;
}

ASTNode* parse_if(const Tokens* tokens, size_t* index) {
  // TODO: Implement if parsing
  return NULL;
}

ASTNode* parse_while(const Tokens* tokens, size_t* index) {
  // TODO: Implement while parsing
  return NULL;
}

ASTNode* parse_for(const Tokens* tokens, size_t* index) {
  // TODO: Implement for parsing
  return NULL;
}