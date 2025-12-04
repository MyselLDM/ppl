#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

// Macro to print both to console and file
#define PRINT_BOTH(log, ...)            \
  do {                                  \
    printf(__VA_ARGS__);                \
    if (log) fprintf(log, __VA_ARGS__); \
  } while (0)

void ast_print(const ASTNode* node, int depth, int is_last, FILE* ast_log) {
  if (!node) return;  // skip null node

  if (!node->token && node->child_current == 0) return;

  // Print prefix for current node
  for (int i = 0; i < depth; i++) {
    if (i == depth - 1) {
      PRINT_BOTH(ast_log, is_last ? "+- " : "|- ");
    } else {
      PRINT_BOTH(ast_log, "|  ");
    }
  }

  if (node->token && node->token->lexeme) {
    PRINT_BOTH(ast_log, "%s: '%s'\n", print_ast_type_node(node->type),
               node->token->lexeme);
  } else {
    PRINT_BOTH(ast_log, "%s\n", print_ast_type_node(node->type));
  }

  for (size_t i = 0; i < node->child_current; i++) {
    if (!node->children[i]) continue;  // skip null
    int child_is_last = 1;

    for (size_t j = node->child_current; j > i; j--) {
      if (node->children[j - 1] != NULL) {
        child_is_last = (j - 1 == i);
        break;
      }
    }
    ast_print(node->children[i], depth + 1, child_is_last, ast_log);
  }
}

// Wrapper to start printing from root
void ast_print_root(const ASTNode* root) {
  FILE* ast_log = fopen("Abstract Syntax Tree.txt", "w");
  if (!ast_log) {
    perror("Failed to open AST log file");
    ast_log = NULL;  // fallback: still print to console
  }
  ast_print(root, 0, 1, ast_log);
  if (ast_log) fclose(ast_log);
}
