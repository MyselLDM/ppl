#include "ast.h"

#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"
#include "putils.h"

// ========================
// AST Management Functions
// ========================

/**
 * ast_create_node
 * ----------------
 * Creates and initializes a new AST node.
 *
 * This function allocates memory for a new AST node and initializes all its
 * fields. The node is created with the specified type and optional token
 * reference. The children array is initially NULL and will be allocated
 * dynamically as children are added.
 *
 * @param type The type of AST node to create (e.g., AST_PROGRAM,
 * AST_STATEMENT_LIST)
 * @param token Pointer to the token associated with this node (can be NULL for
 * non-terminal nodes)
 * @return Pointer to the newly created and initialized ASTNode
 */
ASTNode* ast_create_node(ASTNodeType type, Token* token) {
  // Allocate memory for the new node using safe_malloc (exits on failure)
  ASTNode* node = (ASTNode*)safe_malloc(sizeof(ASTNode));

  // Initialize node fields
  node->type = type;
  node->token = token;       // May be NULL for container nodes
  node->children = NULL;     // Children array starts empty
  node->child_capacity = 0;  // No children initially
  node->child_current = 0;

  DEBUG_PRINT("Created node of type %d\n", type);
  return node;
}

/**
 * ast_add_child
 * --------------
 * Adds a child node to a parent node's children array.
 *
 * This function dynamically expands the parent's children array to accommodate
 * the new child. It uses resize_array to safely reallocate memory for the
 * growing array. This is essential for building the hierarchical AST structure.
 *
 * @param parent Pointer to the parent ASTNode that will receive the child
 * @param child Pointer to the child ASTNode to be added
 */
void ast_add_child(ASTNode* parent, ASTNode* child) {
  // Safety check: ensure both parent and child are valid
  if (!parent || !child) {
    return;
  }

  if (parent->child_capacity == 0) {
    parent->child_capacity = 1;
    parent->children = (ASTNode**)resize_array((void**)parent->children,
                                               parent->child_capacity);
    DEBUG_PRINT("Creating children array for parent of type %d\n",
                parent->type);
  } else if (parent->child_current == parent->child_capacity) {
    parent->child_capacity *= 2;
    parent->children = (ASTNode**)resize_array((void**)parent->children,
                                               parent->child_capacity);
    DEBUG_PRINT("Resizing children to %d for parent of type %d\n",
                parent->child_capacity, parent->type);
  }

  DEBUG_PRINT("Adding child to parent of type %d\n", parent->type);
  parent->children[parent->child_current++] = child;
}

/**
 * ast_free
 * ---------
 * Recursively frees an entire AST and all its allocated memory.
 *
 * This function performs a post-order traversal (children first, then parent)
 * to safely free all nodes in the AST. It frees the children array and the node
 * itself, but NOT the tokens, as those are managed by the Tokens structure.
 *
 * @param root Pointer to the root ASTNode to free (can be any subtree)
 */
void ast_free(ASTNode* root) {
  // Base case: NULL node requires no action
  if (!root) {
    return;
  }

  // Recursively free all children first (post-order traversal)
  for (size_t i = 0; i < root->child_capacity; i++) {
    ast_free(root->children[i]);
  }

  // Free the children array itself
  if (root->children) {
    free(root->children);
  }

  // Finally, free the node itself
  // Note: We don't free the token pointer as tokens are managed separately
  free(root);
}

char* print_ast_type_op(ASTOperator type) {
  switch (type) {
    case OP_ADD:
      return "OP_ADD";
      break;
    case OP_SUB:
      return "OP_SUB";
      break;
    case OP_MUL:
      return "OP_MUL";
      break;
    case OP_DIV:
      return "OP_DIV";
      break;
    case OP_MOD:
      return "OP_MOD";
      break;
    case OP_AND:
      return "OP_AND";
      break;
    case OP_OR:
      return "OP_OR";
      break;
    case OP_NOT:
      return "OP_NOT";
      break;
    case OP_NEG:
      return "OP_NEG";
      break;
    case OP_INC:
      return "OP_INC";
      break;
    case OP_DEC:
      return "OP_DEC";
      break;
  }
}

char* print_ast_type_node(ASTNodeType type) {
  switch (type) {
    case AST_PROGRAM:
      return "AST_PROGRAM";
      break;
    case AST_STATEMENT_LIST:
      return "AST_STATEMENT_LIST";
      break;
    case AST_STMT_EMPTY:
      return "AST_STMT_EMPTY";
      break;
    case AST_STMT_BLOCK:
      return "AST_STMT_BLOCK";
      break;
    case AST_STMT_ASSIGN:
      return "AST_STMT_ASSIGN";
      break;
    case AST_STMT_EXPR:
      return "AST_STMT_EXPR";
      break;
    case AST_STMT_IF:
      return "AST_STMT_IF";
      break;
    case AST_STMT_IF_ELSE:
      return "AST_STMT_IF_ELSE";
      break;
    case AST_STMT_PRINT:
      return "AST_STMT_PRINT";
      break;
    case AST_STMT_WHILE:
      return "AST_STMT_WHILE";
      break;
    case AST_STMT_FOR:
      return "AST_STMT_FOR";
      break;
    case AST_FOR_INIT:
      return "AST_FOR_INIT";
      break;
    case AST_FOR_COND:
      return "AST_FOR_COND";
      break;
    case AST_FOR_POST:
      return "AST_FOR_POST";
      break;
    case AST_IDENTIFIER:
      return "AST_IDENTIFIER";
      break;
    case AST_LITERAL_INT:
      return "AST_LITERAL_INT";
      break;
    case AST_LITERAL_FLOAT:
      return "AST_LITERAL_FLOAT";
      break;
    case AST_LITERAL_BOOL:
      return "AST_LITERAL_BOOL";
      break;
    case AST_LITERAL_STRING:
      return "AST_LITERAL_STRING";
      break;
    case AST_LITERAL_CHAR:
      return "AST_LITERAL_CHAR";
      break;
    case AST_GROUPING:
      return "AST_GROUPING";
      break;
    case AST_UNARY_OP:
      return "AST_UNARY_OP";
      break;
    case AST_POSTFIX_OP:
      return "AST_POSTFIX_OP";
      break;
    case AST_BINARY_OP:
      return "AST_BINARY_OP";
      break;
  }
}