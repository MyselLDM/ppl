#ifndef SEMANTIC_H
#define SEMANTIC_H

typedef struct Scope Scope;
typedef struct Symbol Symbol;
typedef struct SemanticContext SemanticContext;

extern SemanticContext* parser_semantic_context;

struct Symbol {
  char* name;
  Symbol* next;
};

struct Scope {
  Scope* parent;
  Symbol* symbol_list;
  Symbol* symbol_list_tail;
};

struct SemanticContext {
  Scope* current_scope;
  int panic_mode;
};

SemanticContext* semantic_init();
void semantic_scope_push();
void semantic_scope_pop();
void semantic_symbol_insert(char* name);
int semantic_symbol_peek(char* name);

#endif