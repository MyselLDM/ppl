
// ================================
// PROGRAM WORKFLOW OVERVIEW
// ================================

// This is the overview structure of the program.
// Thank you for actually reading this!
// What is presented below is the workflow tree of the program.
// Your task will be to write the C files for each of the function prototypes.
// Please select one and notify me of your code progress.

tokenizer_token_scan_manual()  // ---> Tokens (WE ALREADY DID THIS)
    | parse_tokens()           // ---> AST_NODE_PROGRAM
    | parse_statement()  // ---> AST_NODE_STATEMENT (var, print, if, for, while,
                         // assignment)
    | --->parse_expression()--->AST_NODE_EXPRESSION / AST_NODE_LITERAL
          / AST_NODE_OPERATOR
    | --->parse_block()--->AST_NODE_BLOCK(nested statements) |
    parse_error()  // Called on invalid token/structure
    | ast_create_node() / ast_add_child() / ast_free() /
          ast_print()

          // ================================
          // MAIN FUNCTION OVERVIEW
          // ================================

          // The main function will look like this:

          int main() {
  // 1. Load source code (from file or string)
  const char* source_code =
      load_file("program.txt");  // pseudo-code placeholder

  // 2. Lexical Analysis: tokenize the input
  Tokens tokens = tokenizer_token_scan_manual(source_code);

  // 3. Optional: clean/normalize tokens
  token_optimize(&tokens);

  // 4. Optional: debug print tokens to verify lexer
  token_debug_print(&tokens);

  // 5. Parsing: build the AST from tokens
  ASTNode* ast_root = parse_tokens(&tokens);  // <------ WE WILL ADD THIS!!!!!!

  // 6. Print the AST to visualize program structure
  ast_print(ast_root, 0);

  // 7. Cleanup memory
  ast_free(ast_root);
  token_free(&tokens);
  return 0;
}
