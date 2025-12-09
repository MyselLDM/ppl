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
ASTNode* parse_statement(const Tokens* tokens, size_t* index);
