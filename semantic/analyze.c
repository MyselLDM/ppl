#include "analyze.h"

#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"
#include "../syntax/ast.h"
#include "semantic.h"

void analyze_statement_list(ASTNode* curr);
void analyze_scope(ASTNode* curr);
void analyze_declaration(ASTNode* curr);

void semantic_analyze(ASTNode* root) {
  if (root == NULL) return;

  parser_semantic_context = semantic_init();

  ASTNode* program_stmt_list = root->children[0];

  analyze_scope(program_stmt_list);

  DEBUG_PRINT("Semantic Analysis\n");
}

void analyze_scope(ASTNode* curr) {
  if (curr == NULL) return;

  semantic_scope_push();

  for (int i = 0; i < curr->child_current; i++) {
    analyze_statement_list(curr->children[i]);
  }

  semantic_scope_pop();
}

void analyze_statement_list(ASTNode* curr) {
  if (curr == NULL) return;

  switch (curr->type) {
    case AST_STMT_DECLARE:
      analyze_declaration(curr);
      break;
    case AST_STMT_BLOCK:
      analyze_scope(curr);
      break;
  }

  for (int i = 0; i < curr->child_current; i++) {
    analyze_statement_list(curr->children[i]);
  }
}

void analyze_declaration(ASTNode* curr) {
  char* identifier = curr->children[0]->token->lexeme;

  if (!semantic_symbol_peek(identifier)) {
    semantic_symbol_insert(identifier);
  } else {
    DEBUG_PRINT("Symbol already declared: %s", identifier);
  }

  DEBUG_PRINT("Declaration: %s\n", identifier);
}