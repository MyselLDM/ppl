# MUST be at the very top
cls

gcc lexic/tokenizer.c `
    lexic/tokenizer_helper.c `
    lexic/token.c `
    main.c `
    global/lookup.c `
    global/dictionary.c `
    lexic/scanner.c `
    global/debug_print.c `
    syntax/ast.c `
    syntax/bxparser.c `
    syntax/putils.c `
    syntax/parse_stmt.c `
    syntax/parse_expr.c `
    syntax/astprint.c `
    -o main.exe

if ($LASTEXITCODE -ne 0) {
    Write-Host "Compilation failed. Exiting."
    exit $LASTEXITCODE
}

.\main.exe @args