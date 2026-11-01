#include "symtab.h"
#include <search.h>
#include <stdlib.h>
#include <string.h>

SwitchContext switch_stack[32];
int switch_depth = 0;
void *global_sym_table = NULL;
void *local_sym_table = NULL;
void *sym_table = NULL;
static Symbol *local_list = NULL;
int current_local_offset = -4;
int current_param_offset = 8;
char *current_func_name = NULL;
int string_counter = 0;
int label_counter = 1;
int break_stack[64];
int break_depth = 0;

void add_symbol(const char *name, SymbolType type) {
  Symbol *sym = malloc(sizeof(Symbol));
  sym->name = strdup(name);
  sym->type = type;
  sym->next = NULL;

  switch (type) {
  case TYPE_AUTO:
    sym->offset = current_local_offset;
    current_local_offset -= 4; // shift down 4 for next var
    break;
  case TYPE_PARAM:
    sym->offset = current_param_offset;
    current_param_offset += 4; // shift up 4 for next var
    break;
  case TYPE_EXTERN:
    sym->offset = 0;
    break;
  }

  void **table = (type == TYPE_EXTERN) ? &global_sym_table : &local_sym_table;
  Symbol **found = tsearch(sym, table, compare_symbols);
  if (*found != sym) {
    // var was already in the tree
    free(sym->name);
    free(sym);
  } else if (type != TYPE_EXTERN) {
    sym->next = local_list;
    local_list = sym;
  }
}

Symbol *get_symbol(char *name) {
  Symbol dummy;
  dummy.name = name;
  Symbol **found = tfind(&dummy, &local_sym_table, compare_symbols);
  if (found) {
    return *found;
  }
  found = tfind(&dummy, &global_sym_table, compare_symbols);
  if (found) {
    return *found;
  }
  return NULL;
}

void clear_local_symbols(void) {
  Symbol *cur = local_list;
  while (cur) {
    Symbol *next = cur->next;
    free(cur->name);
    free(cur);
    cur = next;
  }
  local_list = NULL;
  local_sym_table = NULL;
}

// required by tsearch
int compare_symbols(const void *pa, const void *pb) {
  return strcmp(((const Symbol *)pa)->name, ((const Symbol *)pb)->name);
}

void push_switch(int dispatch_lbl, int end_lbl) {
  SwitchContext *sc = &switch_stack[switch_depth++];
  sc->dispatch_lbl = dispatch_lbl;
  sc->end_lbl = end_lbl;
  sc->default_lbl = 0;
  sc->case_count = 0;
}

void pop_switch(void) { switch_depth--; }

void add_case(int val, int lbl) {
  if (switch_depth > 0) {
    SwitchContext *sc = &switch_stack[switch_depth - 1];
    sc->cases[sc->case_count].val = val;
    sc->cases[sc->case_count].lbl = lbl;
    sc->case_count++;
  }
}
