#pragma once
#include "../lexic/token.h"
#include "ast.h"

// ========================
// Parsing Functions
// ========================

/**
 * parse_tokens
 * -------------
 * Entry point for parsing a token stream into an Abstract Syntax Tree (AST).
 * This function analyzes the sequence of tokens produced by the lexer and
 * constructs a hierarchical representation of the program structure.
 *
 * @param tokens Pointer to the Tokens struct containing the lexed tokens.
 * @return Pointer to the root ASTNode representing the program.
 *
 * Notes:
 * - The returned ASTNode should later be freed with ast_free().
 * - Typically calls parse_block or parse_statement internally to build the AST.
 */
ASTNode* parse_tokens(const Tokens* tokens);

ASTNode* parse_statement_list(const Tokens* tokens, size_t* index);

/**
 * parse_expression
 * -----------------
 * Parses a sequence of tokens representing an expression, such as arithmetic
 * operations, logical operations, or literals.
 *
 * @param tokens Pointer to the Tokens struct.
 * @param index Pointer to the current token index (will be updated as tokens
 * are consumed).
 * @return Pointer to the ASTNode representing the expression.
 *
 * Notes:
 * - This function may be recursive to handle nested expressions (e.g.,
 * parentheses).
 * - Should handle operator precedence and associativity correctly.
 * - Does not consume tokens beyond the end of the expression.
 */
ASTNode* parse_expression(const Tokens* tokens, size_t* index);

/**
 * parse_statement
 * ----------------
 * Parses a single statement from the token stream, such as variable
 * declarations, print statements, conditional statements (if/else), or loops
 * (for/while).
 *
 * @param tokens Pointer to the Tokens struct.
 * @param index Pointer to the current token index (will be updated as tokens
 * are consumed).
 * @return Pointer to the ASTNode representing the statement.
 *
 * Notes:
 * - This is called repeatedly to build sequences of statements within blocks.
 * - Statements may contain expressions, which are parsed via parse_expression.
 * - Handles statement-specific structures (e.g., semicolon termination, braces
 * for blocks).
 */
ASTNode* parse_statement(const Tokens* tokens, size_t* index);

/**
 * parse_block
 * ------------
 * Parses a block of statements enclosed in braces { ... }.
 *
 * @param tokens Pointer to the Tokens struct.
 * @param index Pointer to the current token index (will be updated as tokens
 * are consumed).
 * @return Pointer to the ASTNode representing the block.
 *
 * Notes:
 * - Creates a parent AST node containing all statements as child nodes.
 * - Handles nested blocks recursively.
 * - Useful for parsing function bodies, loops, and conditional branches.
 */
ASTNode* parse_block(const Tokens* tokens, size_t* index);

/**
 * parse_error
 * ------------
 * Reports a parsing error at a specific location in the source code.
 *
 * @param message Description of the error.
 * @param line Line number where the error occurred.
 * @param offset Character offset in the line.
 *
 * Notes:
 * - Typically prints an error message and may terminate parsing.
 * - Can be enhanced to include error recovery or logging.
 */
void parse_error(const char* message, size_t line, size_t offset);
