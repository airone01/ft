%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

int yylex(void);
void yyerror(const char *s);

typedef enum {
  TYPE_AUTO,
  TYPE_EXTERN
} SymbolType;

typedef struct {
  char *name;
  SymbolType type;
  int offset; // ebp
} Symbol;

void *sym_table = NULL;
int current_local_offset = -4;

// required by tsearch
int compare_symbols(const void *pa, const void *pb) {
  return strcmp(((const Symbol *)pa)->name, ((const Symbol *)pb)->name);
}

void add_symbol(char *name, SymbolType type) {
  Symbol *sym = malloc(sizeof(Symbol));
  sym->name = strdup(name);
  sym->type = type;

  if (type == TYPE_AUTO) {
    sym->offset = current_local_offset;
    // shift down 4 for next var
    current_local_offset -= 4;
  } else {
    // extern symbols don't use edp offset
    sym->offset = 0;
  }

  // insertion
  Symbol **found = tsearch(sym, &sym_table, compare_symbols);
  if (*found != sym) {
    // var was already in the tree
    free(sym->name);
    free(sym);
  }
}

Symbol *get_symbol(char *name) {
  Symbol dummy;
  dummy.name = name;
  Symbol **found = tfind(&dummy, &sym_table, compare_symbols);
  if (found) {
    return *found;
  }
  return NULL;
}
%}

%union {
  int num;
  char *str;
}

%token <str> IDENTIFIER
%token <num> NUMBER
%token EQUALS SEMICOLON AUTO EXTERN

%%

program:
  | program statement
  | program function_definition
  ;

declarations:
  | declarations declaration
  ;

declaration:
    AUTO auto_list SEMICOLON
  | EXTERN extrn_list SEMICOLON
  ;

auto_list:
    IDENTIFIER { add_symbol($1, TYPE_AUTO); }
  | auto_list ',' IDENTIFIER { add_symbol($3, TYPE_AUTO); }
  ;

extrn_list:
    IDENTIFIER { add_symbol($1, TYPE_EXTERN); }
  | extrn_list ',' IDENTIFIER { add_symbol($3, TYPE_EXTERN); }
  ;

statements_list:
  | statements_list statement
  ;

statement:
  IDENTIFIER EQUALS NUMBER SEMICOLON {
    Symbol *sym = get_symbol($1);
    
    if (sym && sym->type == TYPE_AUTO) {
      printf("\tmov eax, %d\n", $3);
      printf("\tmov [ebp%d], eax ; store val in %s\n", sym->offset, $1);
    } else
      fprintf(stderr, "Error: Unknown or non-auto variable '%s'\n", $1);
  }
  ;

function_definition:
  IDENTIFIER '(' ')' '{' {
    printf("%s:\n", $1);
    printf("\t.long %s + 4\n", $1);
    printf("\tenter 0, 0\n"); 
    // reset offset tracker for new func
    current_local_offset = -4; 
  }
  declarations
  statements_list
  '}' {
    printf("\tleave\n");
    printf("\tret\n");
  }
  ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
  return yyparse();
}
