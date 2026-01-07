#include "semantic.h"

#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"
#include "../syntax/ast.h"

SemanticContext* parser_semantic_context;

SemanticContext* semantic_init() {
  SemanticContext* context = (SemanticContext*)malloc(sizeof(SemanticContext));
  context->current_scope = (Scope*)malloc(sizeof(Scope));
  context->current_scope->symbol_list = NULL;
  context->current_scope->parent = NULL;
  context->panic_mode = 0;

  DEBUG_PRINT("Successfully initialized semantic context");
  return context;
}

void semantic_scope_push() {
  Scope* new_scope = (Scope*)malloc(sizeof(Scope));

  new_scope->parent = parser_semantic_context->current_scope;
  new_scope->symbol_list = NULL;

  parser_semantic_context->current_scope = new_scope;
  DEBUG_PRINT("Pushed scope");
  return;
}

void semantic_scope_pop() {
  Scope* curr = parser_semantic_context->current_scope;
  parser_semantic_context->current_scope = curr->parent;

  // free symbols
  Symbol* sym = curr->symbol_list;
  while (sym) {
    Symbol* next = sym->next;
    free(sym->name);
    free(sym);
    sym = next;
  }
  free(curr);

  DEBUG_PRINT("Popped scope");
}

int semantic_symbol_peek(char* name) {
  Scope* curr = parser_semantic_context->current_scope;

  // Scope Traversal
  while (curr != NULL) {
    Symbol* curr_symbol = curr->symbol_list;

    // Symbol Traversal
    while (curr_symbol != NULL) {
      if (strcmp(curr_symbol->name, name) == 0) {
        DEBUG_PRINT("Symbol found: %s", name);
        return 1;
      };
      curr_symbol = curr_symbol->next;
    }
    curr = curr->parent;
  }
  DEBUG_PRINT("Symbol not found: %s", name);
  return 0;
}

void semantic_symbol_insert(char* name) {
  Symbol* symbol = malloc(sizeof(Symbol));
  symbol->name = strdup(name);
  symbol->next = parser_semantic_context->current_scope->symbol_list;
  parser_semantic_context->current_scope->symbol_list = symbol;

  DEBUG_PRINT("Symbol inserted: %s", name);
}