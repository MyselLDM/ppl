#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

void ast_print(const ASTNode* node, int depth) {
  if (!node) return;

  // Print indentation
  for (int i = 0; i < depth; i++) {
    if (i == depth) {
      printf("  ");
    }
    printf("|");
    if (i == depth - 1) {
      printf("--");
    } else {
      printf("  ");
    }
  }

  // Print node type
  printf("{%s}", print_ast_type_node(node->type));

  // Print token, if available
  if (node->token && node->token->lexeme) {
    printf("(%s)", node->token->lexeme);
  }

  printf("\n");

  // Print children
  for (size_t i = 0; i < node->child_current; i++) {
    ast_print(node->children[i], depth + 1);
  }
}
