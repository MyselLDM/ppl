#include "bxparser.h"

#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"
#include "ast.h"
#include "parse_stmt.h"
#include "putils.h"

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
 * The resulting AST represents the complete program structure and can be used
 * for semantic analysis, code generation, or interpretation.
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
  while (index < tokens->length) {
    // Access token using the correct structure member
    Token* token = &tokens->token[index];

    if (token->token_type == T_INVALID) {
      DEBUG_PRINT("Skipping invalid token\n");
    }

    ASTNode* statement = parse_statement(tokens, &index);
    if (statement) {
      ast_add_child(program, statement);
    } else {
      index++;
    }
  }

  return program;
}

/**
 * parse_statement (Step 5 - TO BE IMPLEMENTED)
 * ---------------------------------------------
 * Parses a single statement from the token stream.
 *
 * This function will determine what kind of statement is being parsed based
 * on the current token and delegate to specialized parsing functions.
 *
 * Planned support:
 * - Variable declarations (var x = 5;)
 * - Print statements (print(x);)
 * - Control flow (if/else, for, while)
 * - Blocks ({ ... })
 * - Assignments (x = 5;)
 *
 * @param tokens Pointer to the Tokens structure
 * @param index Pointer to current token index (updated as tokens are consumed)
 * @return Pointer to the ASTNode representing the parsed statement
 */
ASTNode* parse_statement(const Tokens* tokens, size_t* index) {
  Token* token = &tokens->token[*index];

  switch (token->token_type_special) {
    case TS_VAR:
      DEBUG_PRINT("Parsing variable declaration\n");
      return parse_var(tokens, index);
      break;

    case TS_PRINT:
      DEBUG_PRINT("Parsing print statement\n");
      break;

    case TS_IF:
      DEBUG_PRINT("Parsing if statement\n");
      break;

    case TS_WHILE:
      DEBUG_PRINT("Parsing else statement\n");
      break;

    case TS_FOR:
      DEBUG_PRINT("Parsing for statement\n");
      break;
  }

  (*index)++;
  return NULL;
}