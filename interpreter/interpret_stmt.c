#include "interpret_stmt.h"

#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"

void interpret_stmtlist(ASTNode* node);
void interpret_print(ASTNode* node);
void interpret_assign(ASTNode* node);
void interpret_declare(ASTNode* node);
void interpret_if_matched(ASTNode* node);
void interpret_if_unmatched(ASTNode* node);
void interpret_stmtblock(ASTNode* node);
void interpret_while(ASTNode* node);
void interpret_for(ASTNode* node);

void dispatch_node(ASTNode* node) {
  // DEBUG_PRINT("Dispatching AST Node Type, %s",
  // print_ast_type_node(node->type));
  switch (node->type) {
    case AST_STMT_PRINT:
      interpret_print(node);
      break;
    case AST_STMT_ASSIGN:
      interpret_assign(node);
      break;
    case AST_STMT_DECLARE:
      interpret_declare(node);
      break;
    case AST_STMT_IF_MATCHED:
      interpret_if_matched(node);
      break;
    case AST_STMT_IF_UNMATCHED:
      interpret_if_unmatched(node);
      break;
    case AST_STMT_WHILE:
      interpret_while(node);
      break;
    case AST_STMT_FOR:
      interpret_for(node);
      break;

    case AST_STMT_EXPR:
      DEBUG_PRINT("EXPR_STMT");
      break;

    case AST_STATEMENT_LIST:
      interpret_stmtlist(node);
      break;

    case AST_STMT_BLOCK:
      interpret_stmtblock(node);
      break;

    default:
      DEBUG_PRINT("Unhandled AST node type: %d\n", node->type);
      break;
  }
}

void interpret(ASTNode* root) {
  DEBUG_PRINT("interpreter start");

  // parse the first statement list
  dispatch_node(root->children[0]);
}

void interpret_stmtlist(ASTNode* node) {
  for (size_t i = 0; i < node->child_current; i++) {
    dispatch_node(node->children[i]);
  }
}

void interpret_stmtblock(ASTNode* node) { dispatch_node(node->children[0]); }

void interpret_print(ASTNode* node) {
  DEBUG_PRINT("Print statement");
  // Traverse to the expression child (child[0])
  if (node->child_current > 0) {
    dispatch_node(node->children[0]);
  }
}

void interpret_assign(ASTNode* node) {
  DEBUG_PRINT("Assignment statement");
  // Traverse to identifier (child[0]) and expression (child[1])
  if (node->child_current > 0) {
    dispatch_node(node->children[0]);  // Identifier
  }
  if (node->child_current > 1) {
    dispatch_node(node->children[1]);  // Expression
  }
}

void interpret_declare(ASTNode* node) {
  DEBUG_PRINT("Declaration statement");
  // Traverse to identifier and optional initializer
  if (node->child_current > 0) {
    dispatch_node(node->children[0]);  // Identifier
  }
  if (node->child_current > 1) {
    dispatch_node(node->children[1]);  // Initializer expression
  }
}

void interpret_if_matched(ASTNode* node) {
  DEBUG_PRINT("If-matched statement");
  // Traverse condition (child[0]), then block (child[1]), else block (child[2])
  if (node->child_current > 0) {
    dispatch_node(node->children[0]);  // Condition
  }
  if (node->child_current > 1) {
    dispatch_node(node->children[1]);  // Then block
  }
  if (node->child_current > 2) {
    dispatch_node(node->children[2]);  // Else block
  }
}

void interpret_if_unmatched(ASTNode* node) {
  DEBUG_PRINT("If-unmatched statement");
  // Traverse condition (child[0]) and then block (child[1])
  if (node->child_current > 0) {
    dispatch_node(node->children[0]);  // Condition
  }
  if (node->child_current > 1) {
    dispatch_node(node->children[1]);  // Then block
  }
}

void interpret_while(ASTNode* node) {
  DEBUG_PRINT("While statement");
  // Traverse condition (child[0]) and body (child[1])
  if (node->child_current > 0) {
    dispatch_node(node->children[0]);  // Condition
  }
  if (node->child_current > 1) {
    dispatch_node(node->children[1]);  // Body
  }
}

void interpret_for(ASTNode* node) {
  DEBUG_PRINT("For statement");
  // Traverse init (child[0]), condition (child[1]), post (child[2]), body (child[3])
  if (node->child_current > 0) {
    dispatch_node(node->children[0]);  // Init
  }
  if (node->child_current > 1) {
    dispatch_node(node->children[1]);  // Condition
  }
  if (node->child_current > 2) {
    dispatch_node(node->children[2]);  // Post
  }
  if (node->child_current > 3) {
    dispatch_node(node->children[3]);  // Body
  }
}
