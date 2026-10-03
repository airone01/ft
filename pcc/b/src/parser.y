%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#define CRESET "\e[0m"
#define REDHB "\e[0;37;101m"

int yylex(void);
void yyerror(const char *s);

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

void *sym_table = NULL;
int current_local_offset = -4;
int current_param_offset = 8;

// required by tsearch
int compare_symbols(const void *pa, const void *pb) {
  return strcmp(((const Symbol *)pa)->name, ((const Symbol *)pb)->name);
}

void add_symbol(char *name, SymbolType type) {
  Symbol *sym = malloc(sizeof(Symbol));
  sym->name = strdup(name);
  sym->type = type;

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

%token AUTO EXTERN WHILE IF ELSE RETURN
%token <str> IDENTIFIER
%token <num> NUMBER
%token <str> STRING
%token SEMICOLON COMMA PAROPEN PARCLOSE BRACEOPEN BRACECLOSE ARROPEN ARRCLOSE COMMOPEN COMMCLOSE
%token EQUALS NOTEQUALS LOWEREQ LOWER HIGHEREQ HIGHER
%token EQUAL NOT BITNOT AND BITAND OR BITOR XOR LSHIFT RSHIFT
%token INCREMENT DECREMENT PLUS MINUS STAR DIV MOD

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
  | auto_list COMMA IDENTIFIER { add_symbol($3, TYPE_AUTO); }
  ;

extrn_list:
    IDENTIFIER { add_symbol($1, TYPE_EXTERN); }
  | extrn_list COMMA IDENTIFIER { add_symbol($3, TYPE_EXTERN); }
  ;

param_list:
    IDENTIFIER { add_symbol($1, TYPE_PARAM); }
  | param_list COMMA IDENTIFIER { add_symbol($3, TYPE_PARAM); }
  ;

statements_list:
  | statements_list statement
  ;

lvalue:
  IDENTIFIER {
    Symbol *sym = get_symbol($1);
    if (!sym) {
      fprintf(stderr, REDHB" Error: Unknown variable '%s'"CRESET"\n", $1);
    } else if (sym->type == TYPE_AUTO) {
      printf("  lea eax, [ebp %d]\n", sym->offset);
      printf("  push eax\n");
    } else if (sym->type == TYPE_PARAM) {
      printf("  lea eax, [ebp +  %d]\n", sym->offset);
      printf("  push eax\n");
    } else if (sym->type == TYPE_PARAM) {
      printf("  lea eax, \"%s\"\n", sym->name);
      printf("  push eax\n");
    }
  }

primary_expr:
    IDENTIFIER {
      Symbol *sym = get_symbol($1);
      if (sym->type == TYPE_AUTO) {
        printf("  lea eax, [ebp %d]\n", sym->offset);
        printf("  mov eax, [eax]\n");
        printf("  push eax\n");
      } else if (sym->type == TYPE_PARAM) {
        printf("  lea eax, [ebp + %d]\n", sym->offset);
        printf("  mov eax, [eax]\n");
        printf("  push eax\n");
      } else if (sym->type == TYPE_EXTERN) {
        printf("  lea eax, \"%s\"\n", sym->name);
        printf("  mov eax, [eax]\n");
        printf("  push eax\n");
      }
    }
  | NUMBER {
      printf("  mov eax, %d\n", $1);
      printf("  push eax\n");
    }
  ;

statement:
  lvalue EQUAL primary_expr SEMICOLON {
    // primary_expr left its value in eax for us
    // lvalue pushed its address earlier, now on stack
    printf("  pop ebx\n");
    printf("  mov [ebx], eax\n");
  }
  ;

function_definition:
  IDENTIFIER PAROPEN PARCLOSE BRACEOPEN {
    printf("%s:\n", $1);
    printf("  .long %s + 4\n", $1);
    printf("  enter 0, 0\n"); 
    // reset offset tracker for new func
    current_local_offset = -4; 
  }
  declarations
  statements_list
  BRACECLOSE {
    printf("  leave\n");
    printf("  ret\n");
  }
  ;

%%

void yyerror(const char *s) {
  fprintf(stderr, REDHB" Error: %s "CRESET"\n", s);
}

int main(void) {
  return yyparse();
}
