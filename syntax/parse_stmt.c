#include "parse_stmt.h"

#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"
#include "ast.h"
#include "bxparser.h"
#include "parse_expr.h"
#include "putils.h"

ASTNode* parse_assignment(const Tokens* tokens, size_t* index);
ASTNode* parse_print(const Tokens* tokens, size_t* index);
ASTNode* parse_if(const Tokens* tokens, size_t* index);
ASTNode* parse_while(const Tokens* tokens, size_t* index);
ASTNode* parse_for(const Tokens* tokens, size_t* index);
ASTNode* parse_block(const Tokens* tokens, size_t* index);
ASTNode* parse_condition(const Tokens* tokens, size_t* index);
ASTNode* parse_for_condition(const Tokens* tokens, size_t* index);

ASTNode* parse_assignment(const Tokens* tokens, size_t* index) {
  if (CURRENT_TOKEN.token_type_special == TS_VAR) {
    (*index)++;
    // Noise Word
    if (CURRENT_TOKEN.token_type == T_NOISE) {
      (*index)++;
    }

    if (CURRENT_TOKEN.token_type != T_IDENTIFIER) {
      PARSE_ERROR("Expected variable name");
    }

    Token* identifier = &CURRENT_TOKEN;

    (*index)++;

    if (CURRENT_TOKEN.token_type_special != TS_ASSIGNMENT) {
      PARSE_ERROR("Expected \"=\"");
    }

    (*index)++;

    ASTNode* node_as = ast_create_node(AST_STMT_DECLARE, NULL);
    ASTNode* node_ident = ast_create_node(AST_IDENTIFIER, identifier);
    ASTNode* expr_node = parse_expression(tokens, index);
    CHECK_SEMICOLON;
    ast_add_child(node_as, node_ident);
    ast_add_child(node_as, expr_node);
    return node_as;
  }

  if (CURRENT_TOKEN.token_type != T_IDENTIFIER) {
    PARSE_ERROR("Expected variable name");
  }

  Token* identifier = &CURRENT_TOKEN;
  (*index)++;

  if (CURRENT_TOKEN.token_type_special != TS_ASSIGNMENT) {
    (*index)--;
    ASTNode* expr_node = parse_expression(tokens, index);
    CHECK_SEMICOLON;
    return expr_node;
  }

  (*index)++;
  ASTNode* node_as = ast_create_node(AST_STMT_ASSIGN, NULL);

  ASTNode* node_ident = ast_create_node(AST_IDENTIFIER, identifier);
  ASTNode* expr_node = parse_expression(tokens, index);
  CHECK_SEMICOLON;

  ast_add_child(node_as, node_ident);
  ast_add_child(node_as, expr_node);
  return node_as;
}

ASTNode* parse_print(const Tokens* tokens, size_t* index) {
  (*index)++;
  ASTNode* print = ast_create_node(AST_STMT_PRINT, NULL);
  ASTNode* expr_node = parse_condition(tokens, index);
  CHECK_SEMICOLON;
  ast_add_child(print, expr_node);
  return print;
}

ASTNode* parse_if(const Tokens* tokens, size_t* index) {
  (*index)++;

  // Parse condition and true block
  ASTNode* condition = parse_condition(tokens, index);
  ASTNode* block_true = parse_block(tokens, index);

  // --------- CASE 1: Matched IF -----------
  if (CURRENT_TOKEN.token_type_special == TS_ELSE) {
    (*index)++;
    ASTNode* block_false = parse_block(tokens, index);

    ASTNode* if_matched = ast_create_node(AST_STMT_IF_MATCHED, NULL);
    ast_add_child(if_matched, condition);
    ast_add_child(if_matched, block_true);
    ast_add_child(if_matched, block_false);

    return if_matched;
  }

  // --------- CASE 2: Unmatched IF -----------

  ASTNode* if_unmatched = ast_create_node(AST_STMT_IF_UNMATCHED, NULL);
  ast_add_child(if_unmatched, condition);
  ast_add_child(if_unmatched, block_true);

  return if_unmatched;
}

ASTNode* parse_while(const Tokens* tokens, size_t* index) {
  (*index)++;
  ASTNode* while_node = ast_create_node(AST_STMT_WHILE, NULL);
  ASTNode* condition = parse_condition(tokens, index);
  ASTNode* block = parse_block(tokens, index);

  ast_add_child(while_node, condition);
  ast_add_child(while_node, block);
  return while_node;
}

ASTNode* parse_for(const Tokens* tokens, size_t* index) {
  // TODO: Implement for parsing
  (*index)++;
  ASTNode* for_node = ast_create_node(AST_STMT_FOR, NULL);
  ASTNode* for_condition = parse_for_condition(tokens, index);
  ASTNode* block = parse_block(tokens, index);

  ast_add_child(for_node, for_condition);
  ast_add_child(for_node, block);
  return for_node;
}

ASTNode* parse_for_condition(const Tokens* tokens, size_t* index) {
  ASTNode* for_node = ast_create_node(AST_FOR_CONDITION, NULL);
  ASTNode* for_init_node = ast_create_node(AST_FOR_INIT, NULL);
  ASTNode* for_expression_node = ast_create_node(AST_FOR_EXPR, NULL);
  ASTNode* for_update_node = ast_create_node(AST_FOR_POST, NULL);

  ASTNode* for_init = parse_assignment(tokens, index);
  ASTNode* for_expression = parse_condition(tokens, index);
  ASTNode* for_update = parse_assignment(tokens, index);

  ast_add_child(for_init_node, for_init);
  ast_add_child(for_expression_node, for_expression);
  ast_add_child(for_update_node, for_update);

  ast_add_child(for_node, for_init_node);
  ast_add_child(for_node, for_expression_node);
  ast_add_child(for_node, for_update_node);

  return for_node;
}

ASTNode* parse_condition(const Tokens* tokens, size_t* index) {
  if (CURRENT_TOKEN.token_type_special == TS_L_PAREN) {
    (*index)++;
    ASTNode* condition = ast_create_node(AST_CONDITION, NULL);
    ASTNode* expr = parse_expression(tokens, index);
    if (CURRENT_TOKEN.token_type_special != TS_R_PAREN) {
      PARSE_ERROR("Expected \")\"");
    }
    ast_add_child(condition, expr);
    (*index)++;
    return condition;
  }

  PARSE_ERROR("Expected parenthesis condition");
  return NULL;
}

ASTNode* parse_block(const Tokens* tokens, size_t* index) {
  if (CURRENT_TOKEN.token_type_special == TS_L_BRACE) {
    (*index)++;
    ASTNode* block = ast_create_node(AST_STMT_BLOCK, NULL);
    ASTNode* expr = parse_statement_list(tokens, index);
    if (CURRENT_TOKEN.token_type_special != TS_R_BRACE) {
      PARSE_ERROR("Expected \"}\"");
    }
    ast_add_child(block, expr);
    (*index)++;
    return block;
  }

  PARSE_ERROR("Expected block");
  return NULL;
}