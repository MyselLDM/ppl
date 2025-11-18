#pragma once
#include "../lexic/token.h"

// ========================
// AST Structures
// ========================

typedef enum {
  AST_NODE_PROGRAM,     // Root node representing the entire program
  AST_NODE_STATEMENT,   // Any statement (if, for, var declaration, etc.)
  AST_NODE_EXPRESSION,  // Expressions like arithmetic or logical operations
  AST_NODE_LITERAL,     // Literal values (numbers, strings, true/false)
  AST_NODE_IDENTIFIER,  // Variable names or identifiers
  AST_NODE_OPERATOR,    // Operators (+, -, *, /, etc.)
  AST_NODE_UNKNOWN      // For error recovery or unrecognized constructs
} ASTNodeType;

typedef struct ASTNode {
  ASTNodeType type;           // Type of the AST node
  Token* token;               // Pointer to the token associated with this node
  struct ASTNode** children;  // Dynamic array of child nodes
  size_t child_count;         // Number of children
} ASTNode;

// ========================
// AST Functions
// ========================

/**
 * ast_create_node
 * ----------------
 * Creates a new AST node of the given type and associates it with a token.
 * The token may be NULL for non-terminal nodes that don't directly correspond
 * to a specific token (e.g., program or block nodes).
 *
 * @param type The type of AST node (ASTNodeType).
 * @param token Pointer to a Token struct associated with this node. Can be
 * NULL.
 * @return Pointer to the newly created ASTNode.
 *
 * Notes:
 * - Initializes the child array to NULL and child_count to 0.
 * - Memory allocation should be handled safely (use safe_malloc from utils).
 */
ASTNode* ast_create_node(ASTNodeType type, Token* token);

/**
 * ast_add_child
 * --------------
 * Adds a child node to a parent node's children array.
 * Dynamically resizes the children array if needed.
 *
 * @param parent Pointer to the parent ASTNode.
 * @param child Pointer to the child ASTNode to add.
 *
 * Notes:
 * - Useful for building hierarchical structures like blocks, expressions, and
 * statements.
 * - Child nodes should have been allocated separately (e.g., via
 * ast_create_node).
 * - Updates the parent node's child_count.
 */
void ast_add_child(ASTNode* parent, ASTNode* child);

/**
 * ast_free
 * ---------
 * Recursively frees an AST and all associated memory.
 *
 * @param root Pointer to the root ASTNode to free.
 *
 * Notes:
 * - Frees the children array and all child nodes recursively.
 * - Does NOT free the tokens themselves (tokens are managed separately by
 * Tokens).
 * - Should be called after parsing is done to avoid memory leaks.
 */
void ast_free(ASTNode* root);
