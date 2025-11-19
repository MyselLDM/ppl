#pragma once
#include "../lexic/token.h"

// ========================
// AST Structures
// ========================

/*









DISREGARD FOR NOW
Our tree is not finished due to the cfg's not finalized
will continue after the expression tree












*/

typedef enum {

  // ————————————————
  // Program / Statement
  // ————————————————
  AST_PROGRAM,
  AST_STATEMENT_LIST,
  AST_STATEMENT_EXPR,
  AST_STATEMENT_ASSIGN,

  // ————————————————
  // Expression nodes
  // ————————————————

  // Primary
  AST_IDENTIFIER,
  AST_LITERAL_BOOL,
  AST_LITERAL_INT,
  AST_LITERAL_FLOAT,
  AST_LITERAL_STRING,
  AST_LITERAL_CHAR,
  AST_GROUPING,  // (expr)

  // Unary operators
  AST_UNARY_OP,  // !expr, -expr

  // Binary operators (ALL operators of your CFG)
  AST_BINARY_OP,  // +, -, *, /, %, ^, <, >, <=, >=, ==, !=, &&, ||

  // Assignment
  AST_ASSIGN,  // id = expr

} ASTNodeType;

typedef enum {
  // Arithmetic
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_MOD,
  OP_EXP,
  OP_DIV_F,

  // Relational
  OP_LT,
  OP_GT,
  OP_LE,
  OP_GE,
  OP_EQ,
  OP_NE,

  // Logical
  OP_AND,
  OP_OR,

  // Unary
  OP_NOT,
  OP_NEG

} ASTOperator;

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
