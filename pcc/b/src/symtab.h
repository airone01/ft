#ifndef SRC_SYMTAB_H
#define SRC_SYMTAB_H

typedef enum {
  /* Local variables. Stack-allocated below ebp.
   * Start at offset -4 and decrement by 4 for each variable. */
  TYPE_AUTO,
  /* Function arguments. Caller-passed above ebp.
   * Start at offset +8 and increment by 4 for each parameter. */
  TYPE_PARAM,
  /* Global/extern symbols. Referenced by name.
   * No stack offset. */
  TYPE_EXTERN
} SymbolType;

typedef struct {
  char *name;
  SymbolType type;
  int offset; // ebp
} Symbol;

typedef struct {
  int val;
  int lbl;
} CaseEntry;

typedef struct {
  int dispatch_lbl;
  int end_lbl;
  int default_lbl;
  CaseEntry cases[128];
  int case_count;
} SwitchContext;

extern SwitchContext switch_stack[32];
extern int switch_depth;
extern void *sym_table;
extern int current_local_offset;
extern int current_param_offset;
extern char *current_func_name;
extern int string_counter;
extern int label_counter;

void add_symbol(char *name, SymbolType type);
Symbol *get_symbol(char *name);
int compare_symbols(const void *pa, const void *pb);

void push_switch(int dispatch_lbl, int end_lbl);
void pop_switch(void);
void add_case(int val, int lbl);

#endif /* SRC_SYMTAB_H */
