#include "bxparser.h"
#include "putils.h"
#include <stdio.h>
#include <stdlib.h>

// ========================
// Parsing Error Function
// ========================

/**
 * parse_error
 * ------------
 * Reports a parsing error and terminates the program.
 * 
 * This function prints a formatted error message to stderr with the error location
 * and then exits the program with a failure status. In a production parser, this
 * could be enhanced to support error recovery.
 * 
 * @param message Description of the parsing error
 * @param line Line number where the error occurred
 * @param offset Character offset within the line where the error occurred
 */
void parse_error(const char* message, size_t line, size_t offset)
{
  fprintf(stderr, "[PARSE ERROR] %s at line %zu, offset %zu\n", message, line, offset);
  exit(EXIT_FAILURE);
}

// ========================
// Parsing Functions
// ========================

/**
 * parse_tokens (Step 4)
 * ----------------------
 * Entry point for the parser that converts a token stream into an AST.
 * 
 * This function creates the root AST_PROGRAM node and calls parse_statement
 * repeatedly to fill the program. It automatically skips noise tokens (whitespace,
 * comments) to focus on meaningful syntax.
 * 
 * The resulting AST represents the complete program structure and can be used
 * for semantic analysis, code generation, or interpretation.
 * 
 * @param tokens Pointer to the Tokens structure containing all lexed tokens
 * @return Pointer to the root ASTNode (AST_PROGRAM), or NULL if tokens are empty
 */
ASTNode* parse_tokens(const Tokens* tokens)
{
  // Validate input: ensure we have tokens to parse
  if (!tokens || tokens->length == 0)
  {
    return NULL;
  }
  
  // Create the root program node (no associated token)
  ASTNode* program = ast_create_node(AST_PROGRAM, NULL);
  
  // Initialize index to track position in token stream
  size_t index = 0;
  
  // Iterate through all tokens in the stream
  while (index < tokens->length)
  {
    // Access token using the correct structure member
    Token* token = &tokens->token[index];
    
    // Skip noise tokens (whitespace, newlines) and comments
    if (token->token_type == T_NOISE || token->token_type == T_COMMENT)
    {
      index++;
      continue;
    }
    
    // Parse the next statement and add it to the program
    // NOTE: parse_statement is Step 5 - to be implemented later
    ASTNode* statement = parse_statement(tokens, &index);
    if (statement)
    {
      ast_add_child(program, statement);
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
ASTNode* parse_statement(const Tokens* tokens, size_t* index)
{
  // TODO: Implement statement parsing
  // For now, create a placeholder node and advance past one token
  if (*index < tokens->length)
  {
    Token* token = &tokens->token[*index];
    (*index)++;
    return ast_create_node(AST_STATEMENT_EXPR, token);
  }
  return NULL;
}

/**
 * parse_expression (TO BE IMPLEMENTED)
 * -------------------------------------
 * Parses an expression from the token stream.
 * 
 * Will handle: literals, identifiers, parenthesized expressions,
 * and binary operators with proper precedence.
 * 
 * @param tokens Pointer to the Tokens structure
 * @param index Pointer to current token index (updated as tokens are consumed)
 * @return Pointer to the ASTNode representing the expression
 */
ASTNode* parse_expression(const Tokens* tokens, size_t* index)
{
  // TODO: Implement expression parsing
  return NULL;
}

/**
 * parse_block (TO BE IMPLEMENTED)
 * --------------------------------
 * Parses a block of statements enclosed in braces { ... }.
 * 
 * @param tokens Pointer to the Tokens structure
 * @param index Pointer to current token index (updated as tokens are consumed)
 * @return Pointer to the ASTNode representing the block
 */
ASTNode* parse_block(const Tokens* tokens, size_t* index)
{
  // TODO: Implement block parsing
  return NULL;
}
