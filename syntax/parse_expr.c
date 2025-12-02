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

/*
 Macro: extend 'left' by consuming all occurrences of `current_token` operator.
 Usage: the function must declare and initialize `ASTNode* left =
 <next_level>(...)` and then call RECURSE(...). The macro will:
  - while the current token matches the operator:
      - capture the operator token (op)
      - advance the index
      - parse the right-hand side using NEXT_LEVEL
      - create AST node and attach left/right
      - set left = new node
*/
#define RECURSE(OP_TOKEN, NODE_TYPE, NEXT_LEVEL)             \
  do {                                                       \
    while (CURRENT_TOKEN.token_type_special == (OP_TOKEN)) { \
      Token* op = &CURRENT_TOKEN;                            \
      (*index)++;                                            \
                                                             \
      ASTNode* right_node = NEXT_LEVEL(tokens, index);       \
      ASTNode* new_node = ast_create_node((NODE_TYPE), op);  \
      ast_add_child(new_node, left);                         \
      ast_add_child(new_node, right_node);                   \
      left = new_node;                                       \
    }                                                        \
  } while (0)

ASTNode* parse_expression(const Tokens* tokens, size_t* index) {
  return parse_logical_or(tokens, index);
}

ASTNode* parse_logical_or(const Tokens* tokens, size_t* index) {
  ASTNode* left = parse_logical_and(tokens, index);
  RECURSE(TS_OR, AST_LOGICAL_OR, parse_logical_and);
  return left;
}

ASTNode* parse_logical_and(const Tokens* tokens, size_t* index) {
  ASTNode* left = parse_equality(tokens, index);
  RECURSE(TS_AND, AST_LOGICAL_AND, parse_equality);
  return left;
}

ASTNode* parse_equality(const Tokens* tokens, size_t* index) {
  ASTNode* left = parse_relational(tokens, index);
  /* handle == and != in the same function/loop chain */
  RECURSE(TS_EQUAL, AST_RELATIONAL_EQ, parse_relational);
  RECURSE(TS_NOT_EQUAL, AST_RELATIONAL_NEQ, parse_relational);
  return left;
}

ASTNode* parse_relational(const Tokens* tokens, size_t* index) {
  ASTNode* left = parse_additive(tokens, index);
  RECURSE(TS_LESS_THAN, AST_RELATIONAL_LT, parse_additive);
  RECURSE(TS_LESS_EQUAL, AST_RELATIONAL_LTE, parse_additive);
  RECURSE(TS_GREATER_THAN, AST_RELATIONAL_GT, parse_additive);
  RECURSE(TS_GREATER_EQUAL, AST_RELATIONAL_GTE, parse_additive);
  return left;
}

ASTNode* parse_additive(const Tokens* tokens, size_t* index) {
  ASTNode* left = parse_multiplicative(tokens, index);
  RECURSE(TS_ADD, AST_ADD, parse_multiplicative);
  RECURSE(TS_SUBTRACT, AST_SUB, parse_multiplicative);
  return left;
}

ASTNode* parse_multiplicative(const Tokens* tokens, size_t* index) {
  ASTNode* left = parse_exponential(tokens, index);
  RECURSE(TS_MULTIPLY, AST_MUL, parse_exponential);
  RECURSE(TS_DIVIDE, AST_DIV, parse_exponential);
  RECURSE(TS_MODULO, AST_MOD, parse_exponential);
  RECURSE(TS_DIVIDE_FLOOR, AST_DIV_F, parse_exponential);
  return left;
}

/* exponential must be RIGHT-associative: a ^ b ^ c => a ^ (b ^ c) */
ASTNode* parse_exponential(const Tokens* tokens, size_t* index) {
  ASTNode* left = parse_unary(tokens, index);

  if (CURRENT_TOKEN.token_type_special == TS_POWER) {
    Token* op = &CURRENT_TOKEN;
    (*index)++;
    /* right-associative: parse_exponential on RHS */
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

  /* prefix unary operators: ! and unary - */
  if (t->token_type_special == TS_NOT || t->token_type_special == TS_SUBTRACT) {
    Token* op = t;
    (*index)++;

    ASTNode* operand = parse_unary(tokens, index);
    ASTNode* node = NULL;

    ASTNodeType type =
        (op->token_type_special == TS_SUBTRACT) ? AST_NEG : AST_NOT;
    node = ast_create_node(type, op);

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
    (*index)++;

    ASTNode* post = ast_create_node(type, op);
    ast_add_child(post, node);
    node = post;
  }

  return node;
}

ASTNode* parse_primary(const Tokens* tokens, size_t* index) {
  Token* t = &CURRENT_TOKEN;

  DEBUG_PRINT("Parsing primary: %s", CURRENT_TOKEN.lexeme);

  /* Parenthesized: parse the full top-level expression inside */
  if (t->token_type_special == TS_L_PAREN) {
    (*index)++;
    ASTNode* expr = parse_expression(tokens, index);
    if (CURRENT_TOKEN.token_type_special != TS_R_PAREN) {
      PARSE_ERROR("Expected \")\"");
    }
    (*index)++;
    return expr; /* returning inner expression is fine; if you want grouping
                    node, wrap it */
  }

  switch (t->token_type_special) {
    case TS_INTEGER_LITERAL:
      (*index)++;
      return ast_create_node(AST_LITERAL_INT, t);
    case TS_FLOAT:
      (*index)++;
      return ast_create_node(AST_LITERAL_FLOAT, t);
    case TS_STRING:
      (*index)++;
      return ast_create_node(AST_LITERAL_STRING, t);
    case TS_IDENTIFIER:
      (*index)++;
      return ast_create_node(AST_IDENTIFIER, t);
    case TS_TRUE:
    case TS_FALSE:
      (*index)++;
      return ast_create_node(AST_LITERAL_BOOL, t);
    default:
      PARSE_ERROR("Unexpected token in primary expression");
      return NULL; /* unreachable but keeps compiler happy */
  }
}
