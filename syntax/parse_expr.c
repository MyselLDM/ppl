#include "parse_expr.h"

#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"
#include "../global/dictionary.h"
#include "ast.h"
#include "putils.h"

ASTNode* parse_expression(const Tokens* tokens, size_t* index);
ASTNode* parse_logical_or(const Tokens* tokens, size_t* index);
ASTNode* parse_logical_and(const Tokens* tokens, size_t* index);
ASTNode* parse_equality(const Tokens* tokens, size_t* index);
ASTNode* parse_relational(const Tokens* tokens, size_t* index);
ASTNode* parse_additive(const Tokens* tokens, size_t* index);
ASTNode* parse_multiplicative(const Tokens* tokens, size_t* index);
ASTNode* parse_exponential(const Tokens* tokens, size_t* index);
ASTNode* parse_unary(const Tokens* tokens, size_t* index);
ASTNode* parse_postfix(const Tokens* tokens, size_t* index);
ASTNode* parse_primary(const Tokens* tokens, size_t* index);

/* ------------------------------------------------------
   Generalized macro to handle multiple operators at
   the same precedence level (left-to-right)
------------------------------------------------------- */
#define RECURSE_MULTI(OP_LIST, NODE_TYPE_FUNC, NEXT_LEVEL)                 \
  do {                                                                     \
    while (1) {                                                            \
      int matched = 0;                                                     \
      for (size_t i = 0; i < sizeof(OP_LIST) / sizeof(OP_LIST[0]); i++) {  \
        if (CURRENT_TOKEN.token_type_special == OP_LIST[i]) {              \
          matched = 1;                                                     \
          Token* op = &CURRENT_TOKEN;                                      \
          NEXT_TOKEN();                                                    \
          ASTNode* right = NEXT_LEVEL(tokens, index);                      \
          ASTNode* node =                                                  \
              ast_create_node(NODE_TYPE_FUNC(op->token_type_special), op); \
          ast_add_child(node, left);                                       \
          ast_add_child(node, right);                                      \
          left = node;                                                     \
          break;                                                           \
        }                                                                  \
      }                                                                    \
      if (!matched) break;                                                 \
    }                                                                      \
  } while (0)

/* ------------------------------------------------------
   Helper mapping functions for AST node types
------------------------------------------------------- */
static inline ASTNodeType additive_node_type(TokenSpecial ts) {
  switch (ts) {
    case TS_ADD:
      return AST_ADD;
    case TS_SUBTRACT:
      return AST_SUB;
    default:
      return AST_STMT_EMPTY;
  }
}

static inline ASTNodeType multiplicative_node_type(TokenSpecial ts) {
  switch (ts) {
    case TS_MULTIPLY:
      return AST_MUL;
    case TS_DIVIDE:
      return AST_DIV;
    case TS_MODULO:
      return AST_MOD;
    case TS_DIVIDE_FLOOR:
      return AST_DIV_F;
    default:
      return AST_STMT_EMPTY;
  }
}

static inline ASTNodeType equality_node_type(TokenSpecial ts) {
  switch (ts) {
    case TS_EQUAL:
      return AST_RELATIONAL_EQ;
    case TS_NOT_EQUAL:
      return AST_RELATIONAL_NEQ;
    default:
      return AST_STMT_EMPTY;
  }
}

static inline ASTNodeType relational_node_type(TokenSpecial ts) {
  switch (ts) {
    case TS_LESS_THAN:
      return AST_RELATIONAL_LT;
    case TS_LESS_EQUAL:
      return AST_RELATIONAL_LTE;
    case TS_GREATER_THAN:
      return AST_RELATIONAL_GT;
    case TS_GREATER_EQUAL:
      return AST_RELATIONAL_GTE;
    default:
      return AST_STMT_EMPTY;
  }
}

/* ------------------------------------------------------
   Parser functions
------------------------------------------------------- */

ASTNode* parse_expression(const Tokens* tokens, size_t* index) {
  return parse_logical_or(tokens, index);
}

ASTNode* parse_logical_or(const Tokens* tokens, size_t* index) {
  ASTNode* left = parse_logical_and(tokens, index);
  TokenSpecial ops[] = {TS_OR};
  RECURSE_MULTI(ops, relational_node_type /*dummy*/, parse_logical_and);
  return left;
}

ASTNode* parse_logical_and(const Tokens* tokens, size_t* index) {
  ASTNode* left = parse_equality(tokens, index);
  TokenSpecial ops[] = {TS_AND};
  RECURSE_MULTI(ops, relational_node_type /*dummy*/, parse_equality);
  return left;
}

ASTNode* parse_equality(const Tokens* tokens, size_t* index) {
  ASTNode* left = parse_relational(tokens, index);
  TokenSpecial ops[] = {TS_EQUAL, TS_NOT_EQUAL};
  RECURSE_MULTI(ops, equality_node_type, parse_relational);
  return left;
}

ASTNode* parse_relational(const Tokens* tokens, size_t* index) {
  ASTNode* left = parse_additive(tokens, index);
  TokenSpecial ops[] = {TS_LESS_THAN, TS_LESS_EQUAL, TS_GREATER_THAN,
                        TS_GREATER_EQUAL};
  RECURSE_MULTI(ops, relational_node_type, parse_additive);
  return left;
}

ASTNode* parse_additive(const Tokens* tokens, size_t* index) {
  ASTNode* left = parse_multiplicative(tokens, index);
  TokenSpecial ops[] = {TS_ADD, TS_SUBTRACT};
  RECURSE_MULTI(ops, additive_node_type, parse_multiplicative);
  return left;
}

ASTNode* parse_multiplicative(const Tokens* tokens, size_t* index) {
  ASTNode* left = parse_exponential(tokens, index);
  TokenSpecial ops[] = {TS_MULTIPLY, TS_DIVIDE, TS_MODULO, TS_DIVIDE_FLOOR};
  RECURSE_MULTI(ops, multiplicative_node_type, parse_exponential);
  return left;
}

ASTNode* parse_exponential(const Tokens* tokens, size_t* index) {
  ASTNode* left = parse_unary(tokens, index);

  if (CURRENT_TOKEN.token_type_special == TS_POWER) {
    Token* op = &CURRENT_TOKEN;
    NEXT_TOKEN();
    ASTNode* right = parse_exponential(tokens, index);
    ASTNode* node = ast_create_node(AST_POW, op);
    ast_add_child(node, left);
    ast_add_child(node, right);
    return node;
  }
  return left;
}

ASTNode* parse_unary(const Tokens* tokens, size_t* index) {
  Token* t = &CURRENT_TOKEN;
  if (t->token_type_special == TS_NOT || t->token_type_special == TS_SUBTRACT) {
    Token* op = t;
    NEXT_TOKEN();
    ASTNode* operand = parse_unary(tokens, index);
    ASTNodeType type =
        (op->token_type_special == TS_SUBTRACT) ? AST_NEG : AST_NOT;
    ASTNode* node = ast_create_node(type, op);
    ast_add_child(node, operand);
    return node;
  }
  return parse_postfix(tokens, index);
}

ASTNode* parse_postfix(const Tokens* tokens, size_t* index) {
  ASTNode* node = parse_primary(tokens, index);
  while (CURRENT_TOKEN.token_type_special == TS_INCREMENT ||
         CURRENT_TOKEN.token_type_special == TS_DECREMENT) {
    Token* op = &CURRENT_TOKEN;
    ASTNodeType type =
        (op->token_type_special == TS_INCREMENT) ? AST_INC : AST_DEC;
    NEXT_TOKEN();
    ASTNode* post = ast_create_node(type, op);
    ast_add_child(post, node);
    node = post;
  }
  return node;
}

ASTNode* parse_primary(const Tokens* tokens, size_t* index) {
  Token* t = &CURRENT_TOKEN;
  DEBUG_PRINT("Parsing primary: %s", CURRENT_TOKEN.lexeme);

  if (t->token_type_special == TS_L_PAREN) {
    NEXT_TOKEN();
    ASTNode* expr = parse_expression(tokens, index);
    if (CURRENT_TOKEN.token_type_special != TS_R_PAREN) {
      PARSE_ERROR_PAREN();
    }
    NEXT_TOKEN();
    return expr;
  }

  switch (t->token_type_special) {
    case TS_INTEGER_LITERAL:
      NEXT_TOKEN();
      return ast_create_node(AST_LITERAL_INT, t);
    case TS_FLOAT:
      NEXT_TOKEN();
      return ast_create_node(AST_LITERAL_FLOAT, t);
    case TS_STRING:
      NEXT_TOKEN();
      return ast_create_node(AST_LITERAL_STRING, t);
    case TS_IDENTIFIER:
      NEXT_TOKEN();
      return ast_create_node(AST_IDENTIFIER, t);
    case TS_CHAR:
      NEXT_TOKEN();
      return ast_create_node(AST_LITERAL_STRING, t);
    case TS_TRUE:
    case TS_FALSE:
      NEXT_TOKEN();
      return ast_create_node(AST_LITERAL_BOOL, t);
    default:
      PARSE_ERROR_UNEXPECTED_TOKEN("Expected literal or identifier");
  }
  return NULL;  // unreachable
}
