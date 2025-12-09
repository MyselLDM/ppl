#pragma once
#include "../lexic/token.h"
#include "parse_error.h"

#define CURRENT_TOKEN tokens->token[*index]
// ========================
// AST Structures
// ========================

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
  AST_STMT_WRITE,  // return expr
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

ASTNode* ast_create_node(ASTNodeType type, Token* token);

void ast_add_child(ASTNode* parent, ASTNode* child);
void ast_free(ASTNode* root);

char* print_ast_type_op(ASTOperator type);
char* print_ast_type_node(ASTNodeType node);