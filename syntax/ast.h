#pragma once
#include "../lexic/token.h"

#define CURRENT_TOKEN tokens->token[*index]
// ========================
// AST Structures
// ========================

#define PARSE_ERROR(message) \
  parse_error(message, CURRENT_TOKEN.line, CURRENT_TOKEN.offset)

#define CHECK_SEMICOLON                                   \
  if (CURRENT_TOKEN.token_type_special != TS_SEMICOLON) { \
    PARSE_ERROR("Expected \";\"");                        \
  }                                                       \
  (*index)++;

// ========================
// Parsing Error Function
// ========================

/**
 * parse_error
 * ------------
 * Reports a parsing error and terminates the program.
 *
 * This function prints a formatted error message to stderr with the error
 * location and then exits the program with a failure status. In a production
 * parser, this could be enhanced to support error recovery.
 *
 * @param message Description of the parsing error
 * @param line Line number where the error occurred
 * @param offset Character offset within the line where the error occurred
 */

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

  AST_STMT_ASSIGN,   // <AssignmentSTMT>
  AST_STMT_DECLARE,  // var x,   (var x = expr; OR x = expr;)
  AST_STMT_EXPR,     // Expression statement (expr;)

  AST_STMT_IF,            // if (...) block
  AST_STMT_IF_MATCHED,    // if (...) block else block
  AST_STMT_IF_UNMATCHED,  // if (...) ELSE

  AST_STMT_PRINT,  // print(expr)
  AST_STMT_WHILE,  // while(expr) block
  AST_STMT_FOR,    // for(init; cond; post) block

  // for (…) condition parts separated for AST clarity
  AST_FOR_CONDITION,
  AST_FOR_INIT,  // <AssignmentEXP> or NULL
  AST_FOR_EXPR,  // Expression
  AST_FOR_POST,  // Assignment or Expression

  AST_CONDITION,

  // ——————————————————————
  // Expression Types
  // ——————————————————————

  // Primary (literals & identifiers)
  AST_LOGICAL_OR,
  AST_LOGICAL_AND,
  AST_RELATIONAL_EQ,
  AST_RELATIONAL_NEQ,
  AST_RELATIONAL_LT,
  AST_RELATIONAL_LTE,
  AST_RELATIONAL_GT,
  AST_RELATIONAL_GTE,

  AST_ADD,
  AST_SUB,
  AST_MUL,
  AST_DIV,
  AST_MOD,
  AST_DIV_F,
  AST_EXP,
  AST_NOT,
  AST_NEG,
  AST_POW,

  // Unary
  AST_INC,
  AST_DEC,

  // Binary
  AST_IDENTIFIER,
  AST_LITERAL_INT,
  AST_LITERAL_FLOAT,
  AST_LITERAL_BOOL,
  AST_LITERAL_STRING,
  AST_LITERAL_CHAR,

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
void parse_error(const char* message, size_t line, size_t offset);