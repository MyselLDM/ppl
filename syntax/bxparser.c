#include "bxparser.h"

#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"
#include "ast.h"
#include "parse_stmt.h"
#include "putils.h"

ASTNode* parse_tokens(const Tokens* tokens);
ASTNode* parse_statement_list(const Tokens* tokens, size_t* index);

// ========================
// Parsing Functions
// ========================

/**
 * parse_tokens (Step 4)
 * ----------------------
 * Entry point for the parser that converts a token stream into an AST.
 *
 * This function creates the root AST_PROGRAM node and calls parse_statement
 * repeatedly to fill the program. It automatically skips noise tokens
 * (whitespace, comments) to focus on meaningful syntax.
 *
 * The resulting AST represents the complete program structure and can be
 * used for semantic analysis, code generation, or interpretation.
 *
 * @param tokens Pointer to the Tokens structure containing all lexed tokens
 * @return Pointer to the root ASTNode (AST_PROGRAM), or NULL if tokens are
 * empty
 */
ASTNode* parse_tokens(const Tokens* tokens) {
  // Validate input: ensure we have tokens to parse
  if (!tokens || tokens->length == 0) {
    return NULL;
  }

  // Create the root program node (no associated token)
  ASTNode* program = ast_create_node(AST_PROGRAM, NULL);

  // Initialize index to track position in token stream
  size_t index = 0;

  // Iterate through all tokens in the stream
  ASTNode* STMTList = parse_statement_list(tokens, &index);
  ast_add_child(program, STMTList);
  return program;
}

ASTNode* parse_statement_list(const Tokens* tokens, size_t* index) {
  ASTNode* STMTList = ast_create_node(AST_STATEMENT_LIST, NULL);
  while (tokens->length > *index &&
         CURRENT_TOKEN.token_type_special != TS_R_BRACE) {
    ASTNode* stmt = parse_statement(tokens, index);
    ast_add_child(STMTList, stmt);
  }

  return STMTList;
}

ASTNode* parse_statement(const Tokens* tokens, size_t* index) {
  switch (CURRENT_TOKEN.token_type_special) {
    case TS_IDENTIFIER:
    case TS_VAR:
      return parse_assignment(tokens, index);
    case TS_PRINT:
      return parse_print(tokens, index);
    case TS_IF:
      return parse_if(tokens, index);
    case TS_WHILE:
      return parse_while(tokens, index);
    case TS_FOR:
      return parse_for(tokens, index);
    case TS_L_BRACE:
      return parse_block(tokens, index);
    default:
      PARSE_ERROR("Unexpected token in statement");
  }
}