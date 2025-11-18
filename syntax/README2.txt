// -------------------------
// LEXICAL ANALYSIS
// WE ALREADY DID THIS!!!!!!!!!!!!!!!!!!!!!!
// -------------------------

// Step 1: Tokenize the source code
Tokens tokens = tokenizer_token_scan_manual(source_code);
//   - Reads the input string
//   - Identifies lexemes: keywords, identifiers, literals, operators, delimiters
//   - Returns a dynamic array of tokens

// Step 2: Optional token cleanup
token_optimize(&tokens);
//   - Removes noise tokens (whitespace, comments if needed)
//   - Merges multi-character operators
//   - Normalizes token stream for parsing

// Step 3: Debug print tokens (optional)
token_debug_print(&tokens);
//   - Prints tokens with type, special type, line, offset, and lexeme




// THE START WILL BE HERE
// Incase readmejs isnt enough, heres a more linear explaination:


// This is the overview structure of the program. 
// Thank you for actually reading this!
// What is presented below is the workflow tree of the program.
// Your task will be to write the C files for each of the function prototypes.
// Please select one and notify me of your code progress.



// -------------------------
// PARSING
// -------------------------

// Step 4: Parse tokens into an AST
ASTNode* ast_root = parse_tokens(&tokens);
//   - Entry point for parser
//   - Creates AST_NODE_PROGRAM root
//   - Calls parse_statement repeatedly to fill the program

// Step 5: Parse individual statements
//   - Called internally by parse_tokens
//   - Handles variable declarations, print, if/else, for/while loops, assignments
ASTNode* statement_node = parse_statement(&tokens, &index);
//   - Determines type of statement from current token
//   - Calls parse_expression and parse_block as needed

// Step 6: Parse expressions
//   - Called by parse_statement or recursively by itself
ASTNode* expr_node = parse_expression(&tokens, &index);
//   - Handles literals, identifiers, operators, parentheses
//   - Builds expression trees respecting operator precedence

// Step 7: Parse blocks
//   - Called by parse_statement when encountering '{ ... }'
//   - Creates AST_NODE_BLOCK parent node
ASTNode* block_node = parse_block(&tokens, &index);
//   - Calls parse_statement repeatedly for each statement in the block

// Step 8: Handle parsing errors
//   - Called whenever an unexpected token is found
parse_error("Unexpected token", token->line, token->offset);
//   - Prints error message and may terminate parsing

// -------------------------
// AST MANAGEMENT
// -------------------------

// Step 9: Create AST nodes
ASTNode* new_node = ast_create_node(node_type, token);
//   - Allocates new AST node
//   - Attaches token (may be NULL for non-terminals)
//   - Initializes children array

// Step 10: Add children to AST nodes
ast_add_child(parent_node, child_node);
//   - Adds a child node to parent
//   - Resizes parent’s children array if needed

// Step 11: Traverse or print AST
ast_print(ast_root, 0);
//   - Recursively prints AST with indentation
//   - Shows structure of program (statements, expressions, blocks)

// Step 12: Free AST memory
ast_free(ast_root);
//   - Recursively frees all nodes
//   - Prevents memory leaks

// -------------------------
// CLEANUP
// -------------------------

// Step 13: Free token memory
token_free(&tokens);
//   - Frees token array and any dynamically allocated lexemes
