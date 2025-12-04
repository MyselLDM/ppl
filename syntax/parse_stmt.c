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
    ASTNode* node_as = ast_create_node(AST_STMT_DECLARE, &CURRENT_TOKEN);
    NEXT_TOKEN();
    // Noise Word
    DEBUG_PRINT("CURRENT LEXEME %s TYPE: %s", CURRENT_TOKEN.lexeme,
                ts2str(CURRENT_TOKEN.token_type_special));
    if (CURRENT_TOKEN.token_type == T_NOISE) {
      NEXT_TOKEN();
    }

    if (CURRENT_TOKEN.token_type != T_IDENTIFIER) {
      PARSE_ERROR_UNEXPECTED_TOKEN("Expected identifier");
    }

    Token* identifier = &CURRENT_TOKEN;

    NEXT_TOKEN();

    if (CURRENT_TOKEN.token_type_special != TS_ASSIGNMENT) {
      if (CURRENT_TOKEN.token_type_special == TS_SEMICOLON) {
        ASTNode* node_ident = ast_create_node(AST_IDENTIFIER, identifier);
        ast_add_child(node_as, node_ident);
        return node_as;
      }
      PARSE_ERROR_UNEXPECTED_TOKEN("Expected =");
    }

    NEXT_TOKEN();

    ASTNode* node_ident = ast_create_node(AST_IDENTIFIER, identifier);
    ASTNode* expr_node = parse_expression(tokens, index);

    DEBUG_PRINT("RETURNED TO ASSIGNMENT");
    ast_add_child(node_as, node_ident);
    ast_add_child(node_as, expr_node);
    return node_as;
  }
  ASTNode* node_as = ast_create_node(AST_STMT_ASSIGN, &CURRENT_TOKEN);

  if (CURRENT_TOKEN.token_type != T_IDENTIFIER) {
    PARSE_ERROR_UNEXPECTED_TOKEN("Expected identifier");
  }

  Token* identifier = &CURRENT_TOKEN;
  NEXT_TOKEN();

  if (CURRENT_TOKEN.token_type_special != TS_ASSIGNMENT) {
    (*index)--;
    ASTNode* expr_node = parse_expression(tokens, index);
    ast_add_child(node_as, expr_node);
    return node_as;
  }

  NEXT_TOKEN();

  ASTNode* node_ident = ast_create_node(AST_IDENTIFIER, identifier);
  ASTNode* expr_node = parse_expression(tokens, index);

  ast_add_child(node_as, node_ident);
  ast_add_child(node_as, expr_node);
  return node_as;
}

ASTNode* parse_print(const Tokens* tokens, size_t* index) {
  ASTNode* print = ast_create_node(AST_STMT_PRINT, &CURRENT_TOKEN);
  NEXT_TOKEN();
  ASTNode* expr_node = parse_condition(tokens, index);
  CHECK_SEMICOLON;
  ast_add_child(print, expr_node);
  return print;
}

ASTNode* parse_write(const Tokens* tokens, size_t* index) {
  DEBUG_PRINT("WRITE");
  ASTNode* write = ast_create_node(AST_STMT_WRITE, &CURRENT_TOKEN);
  NEXT_TOKEN();

  if (CURRENT_TOKEN.token_type_special != TS_L_PAREN) {
    PARSE_ERROR_PAREN();
  }
  NEXT_TOKEN();

  if (CURRENT_TOKEN.token_type != T_IDENTIFIER) {
    PARSE_ERROR_UNEXPECTED_TOKEN("Expected identifier");
  }
  ASTNode* ident_node = ast_create_node(AST_IDENTIFIER, &CURRENT_TOKEN);
  NEXT_TOKEN();

  if (CURRENT_TOKEN.token_type_special != TS_R_PAREN) {
    PARSE_ERROR_PAREN();
  }
  NEXT_TOKEN();
  CHECK_SEMICOLON;
  ast_add_child(write, ident_node);
  return write;
}

ASTNode* parse_if(const Tokens* tokens, size_t* index) {
  NEXT_TOKEN();

  // Parse condition and true block
  ASTNode* condition = parse_condition(tokens, index);
  ASTNode* block_true = parse_block(tokens, index);

  // --------- CASE 1: Matched IF -----------
  if (CURRENT_TOKEN.token_type_special == TS_ELSE) {
    NEXT_TOKEN();
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
  ASTNode* while_node = ast_create_node(AST_STMT_WHILE, &CURRENT_TOKEN);
  NEXT_TOKEN();
  ASTNode* condition = parse_condition(tokens, index);
  ASTNode* block = parse_block(tokens, index);

  ast_add_child(while_node, condition);
  ast_add_child(while_node, block);
  return while_node;
}

ASTNode* parse_for(const Tokens* tokens, size_t* index) {
  // TODO: Implement for parsing
  ASTNode* for_node = ast_create_node(AST_STMT_FOR, &CURRENT_TOKEN);
  NEXT_TOKEN();
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

  if (CURRENT_TOKEN.token_type_special != TS_L_PAREN) {
    PARSE_ERROR_PAREN();
  }
  NEXT_TOKEN();
  ASTNode* for_init = parse_assignment(tokens, index);
  CHECK_SEMICOLON;
  ASTNode* for_expression = parse_expression(tokens, index);
  CHECK_SEMICOLON;
  ASTNode* for_update = parse_assignment(tokens, index);

  ast_add_child(for_init_node, for_init);
  ast_add_child(for_expression_node, for_expression);
  ast_add_child(for_update_node, for_update);

  if (CURRENT_TOKEN.token_type_special != TS_R_PAREN) {
    PARSE_ERROR_PAREN();
  }
  NEXT_TOKEN();

  ast_add_child(for_node, for_init_node);
  ast_add_child(for_node, for_expression_node);
  ast_add_child(for_node, for_update_node);

  return for_node;
}

ASTNode* parse_condition(const Tokens* tokens, size_t* index) {
  if (CURRENT_TOKEN.token_type_special == TS_L_PAREN) {
    NEXT_TOKEN();
    ASTNode* condition = ast_create_node(AST_CONDITION, NULL);
    ASTNode* expr = parse_expression(tokens, index);
    if (CURRENT_TOKEN.token_type_special != TS_R_PAREN) {
      PARSE_ERROR_PAREN();
    }
    ast_add_child(condition, expr);
    NEXT_TOKEN();
    return condition;
  }

  PARSE_ERROR_PAREN();
}

ASTNode* parse_block(const Tokens* tokens, size_t* index) {
  if (CURRENT_TOKEN.token_type_special == TS_L_BRACE) {
    NEXT_TOKEN();
    ASTNode* block = ast_create_node(AST_STMT_BLOCK, &CURRENT_TOKEN);
    ASTNode* expr = parse_statement_list(tokens, index);
    if (CURRENT_TOKEN.token_type_special != TS_R_BRACE) {
      PARSE_ERROR_BLOCK();
    }
    ast_add_child(block, expr);
    NEXT_TOKEN();
    return block;
  }

  PARSE_ERROR_BLOCK();
  return NULL;
}