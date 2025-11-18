#pragma once
#include "../lexic/token.h"

// ========================
// Lexical Analysis Functions
// ========================

/**
 * tokenizer_token_scan_manual
 * ----------------------------
 * Scans the given input string and produces a dynamic array of tokens.
 * This function performs lexical analysis: it reads characters, groups them
 * into lexemes, and classifies them according to their TokenType and
 * TokenSpecial.
 *
 * @param input Pointer to the null-terminated input string (source code).
 * @return Tokens struct containing:
 *   - token: dynamically allocated array of Token objects
 *   - length: number of tokens identified
 *   - capacity: internal allocated size (may be larger than length)
 *
 * Notes:
 * - Tokens may include keywords, identifiers, constants, operators, delimiters,
 * etc.
 * - The caller is responsible for freeing the Tokens struct with token_free().
 * - Comments are typically ignored or not included in the returned token
 * stream.
 */
Tokens tokenizer_token_scan_manual(const char* input);

/**
 * token_optimize
 * ---------------
 * Cleans and optimizes a token stream after lexical analysis.
 * This may include:
 *   - Removing noise tokens (e.g., whitespace or unused placeholders)
 *   - Merging adjacent tokens if necessary (e.g., multi-character operators)
 *   - Normalizing tokens for easier parsing
 *
 * @param tokens Pointer to the Tokens struct to optimize.
 *
 * Notes:
 * - Modifies the tokens in place.
 * - Should be called before passing tokens to the parser to simplify syntax
 * analysis.
 */
void token_optimize(Tokens* tokens);

/**
 * token_debug_print
 * -----------------
 * Prints all tokens in the given Tokens struct in a human-readable format.
 * Useful for debugging and verifying that the lexer correctly recognized
 * tokens.
 *
 * @param tokens Pointer to the Tokens struct to print.
 *
 * Notes:
 * - Prints token type, token special type, lexeme, and position (line and
 * offset).
 * - Does not modify the token stream.
 */
void token_debug_print(const Tokens* tokens);

/**
 * token_free
 * ----------
 * Frees all memory associated with a Tokens struct, including the array of
 * Token objects.
 *
 * @param tokens Pointer to the Tokens struct to free.
 *
 * Notes:
 * - After calling this, the Tokens struct should not be used unless
 * reinitialized.
 * - Does NOT free the strings inside each Token if they are static or string
 * literals. If dynamic strings are used for lexemes, those must also be freed
 * here.
 */
void token_free(Tokens* tokens);
