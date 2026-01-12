#include "analyze.h"

#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"
#include "../syntax/ast.h"
#include "semantic.h"

void analyze_statement_list(ASTNode* curr);
void analyze_scope(ASTNode* curr);
void analyze_declaration(ASTNode* curr);
void analyze_expression(ASTNode* curr);

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
    case AST_STMT_EXPR:
    case AST_STMT_ASSIGN:
    case AST_STMT_PRINT:
    case AST_STMT_WRITE:
    case AST_STMT_IF:
    case AST_STMT_IF_MATCHED:
    case AST_STMT_IF_UNMATCHED:
    case AST_STMT_WHILE:
    case AST_STMT_FOR:
      // These statements may contain expressions with identifiers
      analyze_expression(curr);
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

void analyze_expression(ASTNode* curr) {
  if (curr == NULL) return;

  // If this node is an identifier, mark it as used
  if (curr->type == AST_IDENTIFIER) {
    char* identifier = curr->token->lexeme;
    if (semantic_symbol_peek(identifier)) {
      semantic_symbol_mark_used(identifier);
      DEBUG_PRINT("Variable used: %s", identifier);
    } else {
      DEBUG_PRINT("Undeclared variable used: %s", identifier);
    }
  }

  // Recursively analyze all child expressions
  for (int i = 0; i < curr->child_current; i++) {
    analyze_expression(curr->children[i]);
  }
}