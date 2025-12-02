#include "parse_stmt.h"

#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"
#include "ast.h"
#include "parse_expr.h"
#include "putils.h"

#define TOKEN tokens->token[*index]
#define PARSE_ERROR(message) parse_error(message, TOKEN.line, TOKEN.offset)

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
void parse_error(const char* message, size_t line, size_t offset) {
  DEBUG_PRINT("[PARSE ERROR] '%s' at line %zu, offset %zu\n", message, line,
              offset);
  exit(EXIT_FAILURE);
}

ASTNode* parse_var(const Tokens* tokens, size_t* index) {
  (*index)++;

  // Noise Word
  if (TOKEN.token_type == T_NOISE) {
    (*index)++;
  }

  if (TOKEN.token_type != T_IDENTIFIER) {
    PARSE_ERROR("Expected variable name");
  }

  Token* identifier = &TOKEN;

  (*index)++;

  if (TOKEN.token_type_special != TS_ASSIGNMENT) {
    PARSE_ERROR("Expected \"=\"");
  }

  (*index)++;

  ASTNode* node_as = ast_create_node(AST_STMT_ASSIGN, NULL);
  ASTNode* node_ident = ast_create_node(AST_IDENTIFIER, identifier);
  ASTNode* expr_node = parse_expression(tokens, index);

  ast_add_child(node_as, node_ident);
  ast_add_child(node_as, expr_node);
  return NULL;
}

ASTNode* parse_print(const Tokens* tokens, size_t* index) {
  // TODO: Implement print parsing
  return NULL;
}

ASTNode* parse_if(const Tokens* tokens, size_t* index) {
  // TODO: Implement if parsing
  return NULL;
}

ASTNode* parse_while(const Tokens* tokens, size_t* index) {
  // TODO: Implement while parsing
  return NULL;
}

ASTNode* parse_for(const Tokens* tokens, size_t* index) {
  // TODO: Implement for parsing
  return NULL;
}