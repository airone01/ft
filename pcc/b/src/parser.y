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
int string_counter = 0;
int label_counter = 1;

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

%type <num> args args_list
%type <num> params params_list
%type <num> while_start

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
    IDENTIFIER {
      add_symbol($1, TYPE_AUTO);
      printf("  push 0\n");
    }
  | auto_list COMMA IDENTIFIER {
      add_symbol($3, TYPE_AUTO);
      printf("  push 0\n");
    }
  ;

extrn_list:
    IDENTIFIER { add_symbol($1, TYPE_EXTERN); }
  | extrn_list COMMA IDENTIFIER { add_symbol($3, TYPE_EXTERN); }
  ;

params_list:
    IDENTIFIER { add_symbol($1, TYPE_PARAM); }
  | params_list COMMA IDENTIFIER { add_symbol($3, TYPE_PARAM); }
  ;

params:
    /* empty */
  | params_list
  ;

statements_list:
  | statements_list statement
  ;

lvalue:
  IDENTIFIER {
    Symbol *sym = get_symbol($1);
    if (sym) {
      if (sym->type == TYPE_AUTO) {
        printf("  lea eax, [ebp %d]\n", sym->offset);
      } else if (sym->type == TYPE_PARAM) {
        printf("  lea eax, [ebp +  %d]\n", sym->offset);
      } else if (sym->type == TYPE_EXTERN) {
        printf("  lea eax, \"%s\"\n", sym->name);
      }
      printf("  push eax\n");
    } else {
      fprintf(stderr, REDHB" Error: Unknown variable '%s'"CRESET"\n", $1);
    }
  }

expr:
    IDENTIFIER {
      Symbol *sym = get_symbol($1);
      if (sym) {
        if (sym->type == TYPE_AUTO) {
          printf("  lea eax, [ebp %d]\n", sym->offset);
        } else if (sym->type == TYPE_PARAM) {
          printf("  lea eax, [ebp + %d]\n", sym->offset);
        } else if (sym->type == TYPE_EXTERN) {
          printf("  lea eax, \"%s\"\n", sym->name);
        }
        printf("  mov eax, [eax]\n");
      } else {
        fprintf(stderr, REDHB" Error: Unknown variable '%s'"CRESET"\n", $1);
      }
    }
  | NUMBER {
      printf("  mov eax, %d\n", $1);
    }
  | STRING {
      printf("  .section .rodata\n");
      printf("  .LC%d:\n", string_counter);
      printf("    .long .LC%d+4\n", string_counter);
      printf("    .string %s\n", $1);
      printf("  .text\n");
      printf("  mov eax, .LC%d\n", string_counter);
      string_counter++;
    }
  | IDENTIFIER PAROPEN {
      Symbol *sym = get_symbol($1);
      if (!sym || sym->type  == TYPE_EXTERN) {
        printf("  lea eax, \"%s\"\n", $1);
      } else if (sym->type  == TYPE_AUTO) {
        printf("  lea eax, [ebp %d]\n", sym->offset);
      } else if (sym->type  == TYPE_PARAM) {
        printf("  lea eax, [ebp + %d]\n", sym->offset);
      }
      printf("  mov eax, [eax]\n");
      printf("  push eax\n");
    }
    args PARCLOSE {
      int num_args = $4;
      if (num_args > 0) {
        // Swap top of stack [esp+0] with func ptr
        // Mult. by 4 is for word size
        printf("  mov ebx, [esp+0]\n");
        printf("  mov ecx, [esp+%d]\n", num_args * 4);
        printf("  mov [esp+%d], ebx\n", num_args * 4);
        printf("  mov [esp+0], ecx\n");
      }
      printf("  pop eax\n");
      printf("  call eax\n");
      if (num_args > 0) {
        printf("  add esp, %d\n", num_args * 4);
      }
    }
  ;

statement:
    lvalue EQUAL expr SEMICOLON {
      printf("  pop ebx\n");
      printf("  mov [ebx], eax\n");
    }
  | lvalue INCREMENT SEMICOLON {
      // lvalue left var addr pushed on stack
      printf("  pop eax\n");
      printf("  mov ebx, [eax]\n");
      printf("  mov ecx, ebx\n");
      printf("  add ebx, 1\n");
      printf("  mov [eax], ebx\n");
      printf("  mov eax, ecx\n");
    }
  | expr SEMICOLON
  | BRACEOPEN statements_list BRACECLOSE
  | while_statement
  ;

while_start:
  WHILE {
    int start = label_counter;
    label_counter += 2;
    printf(".L%d:\n", start);
    $$ = start;
  }

while_statement:
  while_start PAROPEN expr PARCLOSE {
    int exit_lbl = $1 + 1;
    printf("  cmp eax, 0\n");
    printf("  je .L%d\n", exit_lbl);
  }
  statement {
    int start_lbl = $1;
    int exit_lbl = $1 + 1;
    printf("  jmp .L%d\n", start_lbl);
    printf(".L%d:\n", exit_lbl);
  }
  ;

args:
              { $$ = 0; }
  | args_list { $$ = $1; }
  ;

args_list:
    expr {
      printf("  push eax\n");
      $$ = 1;
    }
  | args_list COMMA expr {
      printf("  push eax\n");
      $$ = $1 + 1;
    }
  ;

function_definition:
  IDENTIFIER PAROPEN {
    // Reset offsets for new function
    // Needs to happen *before* params are read
    current_local_offset = -4; 
    current_param_offset = 8;
  }
  params PARCLOSE BRACEOPEN {
    printf(".globl %s\n", $1);
    printf("%s:\n", $1);
    printf("  .long \"%s\" + 4\n", $1);
    printf("  enter 0, 0\n"); 
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
  printf(".intel_syntax noprefix\n");
  printf(".text\n");
  return yyparse();
}
