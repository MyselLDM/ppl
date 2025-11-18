
// ================================
// MAIN FUNCTION OVERVIEW
// ================================

// The main function will look like this:

int main() {
    // 1. Load source code (from file or string)
    const char* source_code = load_file("program.txt"); // pseudo-code placeholder

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
