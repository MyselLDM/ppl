#pragma once
#include "../lexic/token.h"

// ========================
// AST Structures
// ========================

typedef enum {

  // Arithmetic
  OP_ADD,    // +
  OP_SUB,    // -
  OP_MUL,    // *
  OP_DIV,    // /
  OP_MOD,    // %
  OP_DIV_F,  // // (integer division)
  OP_EXP,    // ^

  // Relational
  OP_LT,  // <
  OP_LE,  // <=
  OP_GT,  // >
  OP_GE,  // >=

  // Equality
  OP_EQ,  // ==
  OP_NE,  // !=

  // Logical
  OP_AND,  // &&
  OP_OR,   // ||

  // Unary Prefix
  OP_NOT,  // !
  OP_NEG,  // -

  // Unary Postfix
  OP_INC,  // ++
  OP_DEC   // --

} ASTOperator;

typedef enum {

  // ——————————————————————
  // Program / High-Level Structure
  // ——————————————————————
  AST_PROGRAM,         // <Program>
  AST_STATEMENT_LIST,  // <StatementList>

  // ——————————————————————
  // Statement Types
  // ——————————————————————
  AST_STMT_EMPTY,  // ";" alone
  AST_STMT_BLOCK,  // <BlockStatement>  { ... }

  AST_STMT_ASSIGN,  // <AssignmentSTMT>   (var x = expr; OR x = expr;)
  AST_STMT_EXPR,    // Expression statement (expr;)

  AST_STMT_IF,       // if (...) block
  AST_STMT_IF_ELSE,  // if (...) block else block

  AST_STMT_PRINT,  // print(expr)
  AST_STMT_WHILE,  // while(expr) block
  AST_STMT_FOR,    // for(init; cond; post) block

  // for (…) condition parts separated for AST clarity
  AST_FOR_INIT,  // <AssignmentEXP> or NULL
  AST_FOR_COND,  // Expression
  AST_FOR_POST,  // Assignment or Expression

  // ——————————————————————
  // Expression Types
  // ——————————————————————

  // Primary (literals & identifiers)
  AST_IDENTIFIER,
  AST_LITERAL_INT,
  AST_LITERAL_FLOAT,
  AST_LITERAL_BOOL,
  AST_LITERAL_STRING,
  AST_LITERAL_CHAR,

  AST_GROUPING,  // (expr) use this for each expression parsing & grouping
                 // untill the true expression

  // Unary
  AST_UNARY_OP,    // !expr, -expr
  AST_POSTFIX_OP,  // expr++, expr--

  // Binary
  AST_BINARY_OP,  // + - * / % // ^ < > <= >= == != && ||

} ASTNodeType;

typedef struct ASTNode {
  ASTNodeType type;           // Type of the AST node
  Token* token;               // Pointer to the token associated with this node
  struct ASTNode** children;  // Dynamic array of child nodes
  size_t child_capacity;      // Number of children
  size_t child_current;       // Current child being processed
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

char* print_ast_type_op(ASTOperator type);
char* print_ast_type_node(ASTNodeType node);