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

  DEBUG_PRINT("Created node of type %s", print_ast_type_node(type));
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
    DEBUG_PRINT("Creating children array for parent of type %d", parent->type);
  } else if (parent->child_current == parent->child_capacity) {
    parent->child_capacity *= 2;
    parent->children = (ASTNode**)resize_array((void**)parent->children,
                                               parent->child_capacity);
    DEBUG_PRINT("Resizing children to %d for parent of type %d",
                parent->child_capacity, parent->type);
  }

  DEBUG_PRINT("Adding child to parent of type %d", parent->type);
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

void parse_error(const char* message, size_t line, size_t offset) {
  DEBUG_PRINT("[PARSE ERROR] '%s' at line %zu, offset %zu\n", message, line,
              offset);
  exit(EXIT_FAILURE);
}

char* print_ast_type_op(ASTOperator type) {
  switch (type) {
    case OP_ADD:
      return "OP_ADD";
    case OP_SUB:
      return "OP_SUB";
    case OP_MUL:
      return "OP_MUL";
    case OP_DIV:
      return "OP_DIV";
    case OP_MOD:
      return "OP_MOD";
    case OP_AND:
      return "OP_AND";
    case OP_OR:
      return "OP_OR";
    case OP_NOT:
      return "OP_NOT";
    case OP_NEG:
      return "OP_NEG";
    case OP_INC:
      return "OP_INC";
    case OP_DEC:
      return "OP_DEC";
  }
}

char* print_ast_type_node(ASTNodeType type) {
  switch (type) {
    case AST_PROGRAM:
      return "AST_PROGRAM";
    case AST_STATEMENT_LIST:
      return "AST_STATEMENT_LIST";
    case AST_STMT_EMPTY:
      return "AST_STMT_EMPTY";
    case AST_STMT_BLOCK:
      return "AST_STMT_BLOCK";
    case AST_STMT_ASSIGN:
      return "AST_STMT_ASSIGN";
    case AST_STMT_EXPR:
      return "AST_STMT_EXPR";
    case AST_STMT_IF:
      return "AST_STMT_IF";
    case AST_STMT_IF_ELSE:
      return "AST_STMT_IF_ELSE";
    case AST_STMT_PRINT:
      return "AST_STMT_PRINT";
    case AST_STMT_WHILE:
      return "AST_STMT_WHILE";
    case AST_STMT_FOR:
      return "AST_STMT_FOR";
    case AST_FOR_INIT:
      return "AST_FOR_INIT";
    case AST_FOR_COND:
      return "AST_FOR_COND";
    case AST_FOR_POST:
      return "AST_FOR_POST";
    case AST_IDENTIFIER:
      return "AST_IDENTIFIER";
    case AST_LITERAL_INT:
      return "AST_LITERAL_INT";
    case AST_LITERAL_FLOAT:
      return "AST_LITERAL_FLOAT";
    case AST_LITERAL_BOOL:
      return "AST_LITERAL_BOOL";
    case AST_LITERAL_STRING:
      return "AST_LITERAL_STRING";
    case AST_LITERAL_CHAR:
      return "AST_LITERAL_CHAR";
    case AST_LOGICAL_OR:
      return "||";
    case AST_LOGICAL_AND:
      return "&&";
    case AST_RELATIONAL_EQ:
      return "==";
    case AST_RELATIONAL_NEQ:
      return "!=";
    case AST_RELATIONAL_GT:
      return ">";
    case AST_RELATIONAL_LT:
      return "<";
    case AST_RELATIONAL_GTE:
      return ">=";
    case AST_RELATIONAL_LTE:
      return "<=";
    case AST_ADD:
      return "+";
    case AST_SUB:
      return "-";
    case AST_MUL:
      return "*";
    case AST_DIV:
      return "/";
    case AST_DIV_F:
      return "/_";
    case AST_MOD:
      return "%";
    case AST_NOT:
      return "!";
    case AST_NEG:
      return "-";
    case AST_POW:
      return "^";
    default:
      return "AST_UNKNOWN";
  }
}