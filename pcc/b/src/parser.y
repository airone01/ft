%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#define CRESET "\e[0m"
#define REDHB "\e[0;37;101m"

/* TODO
 * - return
 * - goto
 * - post-in/decrement
 * - array indexing scaled by 4 (`a[b]`)
 * TODO (BONUS)
 * - switch/case
 * - floating point operator
 * - libb
 * - two additional features
 */

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
%type <num> if_header

%nonassoc IFX
%nonassoc ELSE

%token AUTO EXTERN WHILE IF ELSE RETURN
%token <str> IDENTIFIER
%token <num> NUMBER
%token <str> STRING
%token SEMICOLON COMMA PAROPEN PARCLOSE BRACEOPEN BRACECLOSE ARROPEN ARRCLOSE COMMOPEN COMMCLOSE
%token INCREMENT DECREMENT

%right EQUAL
%left OR
%left AND
%left BITOR
%left XOR
%left BITAND
%left EQUALS NOTEQUALS
%left NOT BITNOT
%left LOWER LOWEREQ HIGHER HIGHEREQ
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR DIV MOD

%%

program:
  | /* In B/C, there can only be top-level declarations, no expressions. */
    program declaration
  | program function_definition
  ;

declarations:
    // TODO: figure out if empty case should be here or not
    // Note: In THEORY it's not a problem but it might be better to move it one level higher. Worse clarity for users but may be more understandable to yacc??? idk
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
    /* Load left-value onto stack.
     * It needs to be in the stack because it's the most convenient way to
     * store it for easy access when handling the right-side expression. */
    Symbol *sym = get_symbol($1);
    if (sym) {
      if (sym->type == TYPE_AUTO) {
        printf("  lea eax, [ebp %d]\n", sym->offset);
      } else if (sym->type == TYPE_PARAM) {
        printf("  lea eax, [ebp + %d]\n", sym->offset);
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
      /* Load value where pointed to by variable. Meaning simply loading a variable. */
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
      /* Pretty cool stuff: creates an inline read-only section with the string,
       * and then load its pointer into `eax` ofc */
      printf("  .section .rodata\n");
      printf("  .LC%d:\n", string_counter);
      printf("    .long .LC%d+4\n", string_counter);
      printf("    .string %s\n", $1);
      printf("  .text\n");
      printf("  mov eax, .LC%d\n", string_counter);
      string_counter++;
    }
  | IDENTIFIER PAROPEN {
      /* Load function from pointer */
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
    args /* Load arguments to stack */
    PARCLOSE {
      /* Run function from loaded pointer */
      int num_args = $4;
      if (num_args > 0) {
        /* Must arrange stack again before `call`
         * So swap top of stack [esp+0] with func ptr if func had args
         * (Multiplication by 4 is for word size) */
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
  | lvalue EQUAL expr {
      /* Assignment as expression
       * (eg `var = ...` in if condition) */
      printf("  pop ebx\n");
      printf("  mov [ebx], eax\n");
    }
  /*
   * Math operations
   */
  | expr PLUS expr { // Addition
      printf("  pop ebx\n");
      printf("  add eax, ebx\n");
    }
  | expr MINUS expr { // Substraction
      printf("  pop ebx\n");
      printf("  sub eax ebx\n");
    }
  | expr STAR expr { // Multiplication
      printf("  pop ebx\n");
      printf("  mul ebx\n");
    }
  | expr DIV expr { // Division
      printf("  mov ebx, eax\n"); // Divisor
      printf("  pop eax\n");      // Dividend
      /* "Convert Doubleword to Quadword"
       * Sign-extend `eax` into `edx`. */
      printf("  cdq\n");
      printf("  idiv ebx\n");
    }
  | expr MOD expr { // Modulo
      printf("  mov ebx, eax\n"); // Divisor
      printf("  pop eax\n");      // Dividend
      /* "Convert Doubleword to Quadword"
       * Sign-extend `eax` into `edx`. */
      printf("  cdq\n");
      printf("  idiv ebx\n");
      printf("  mov eax, edx\n"); // Remainder in edx
    }
  /* Note for mid-rule actions:
   * Because we don't have an AST, we must do some bullshit in order for the
   * code to be continuous and working.
   * For each of the following token handled, it goes roughly like this:
   * - Left `expr` evaluates and leaves result in `eax` for us
   *   - This is conveninent for other uses, but not here
   * - Hence we push back `eax`
   * - Right `expr` evaluates and leaves result in `eax` again
   * - End action
   *   - Pops left operand into `ebx`
   *   - Use it as well as `eax` to run operation
   */
  /*
   * Number comparisons
   *
   * `set*` are the calculation themselves
   * `movzx eax, al` left-appends zeroes to `al`.
   */
  | expr LOWER { printf("  push eax\n"); } expr {
      printf("  pop ebx\n");
      printf("  cmp ebx, eax\n");
      printf("  setl al\n");
      printf("  movzx eax, al\n");
    }
  | expr LOWEREQ { printf("  push eax\n"); } expr {
      printf("  pop ebx\n");
      printf("  cmp ebx, eax\n");
      printf("  setle al\n");
      printf("  movzx eax, al\n");
    }
  | expr HIGHER { printf("  push eax\n"); } expr {
      printf("  pop ebx\n");
      printf("  cmp ebx, eax\n");
      printf("  setg al\n");
      printf("  movzx eax, al\n");
    }
  | expr HIGHEREQ { printf("  push eax\n"); } expr {
      printf("  pop ebx\n");
      printf("  cmp ebx, eax\n");
      printf("  setge al\n");
      printf("  movzx eax, al\n");
    }
  | expr EQUALS { printf("  push eax\n"); } expr {
      printf("  pop ebx\n");
      printf("  cmp ebx, eax\n");
      printf("  sete al\n");
      printf("  movzx eax, al\n");
    }
  | expr NOTEQUALS { printf("  push eax\n"); } expr {
      printf("  pop ebx\n");
      printf("  cmp ebx, eax\n");
      printf("  setne al\n");
      printf("  movzx eax, al\n");
    }
  /*
   * Bitwise comparisons
   */
  | expr BITAND { printf("  push eax\n"); } expr {
      printf("  pop ebx\n");
      printf("  and eax, ebx\n");
    }
  | expr BITOR { printf("  push eax\n"); } expr {
      printf("  pop ebx\n");
      printf("  or eax, ebx\n");
    }
  | expr XOR { printf("  push eax\n"); } expr {
      printf("  pop ebx\n");
      printf("  xor eax, ebx\n");
    }
  /*
   * Bit shifts
   */
  | expr LSHIFT { printf("  push eax\n"); } expr {
      printf("  mov ecx, eax\n");
      printf("  pop eax\n");
      printf("  shl eax, cl\n");
    }
  | expr RSHIFT { printf("  push eax\n"); } expr {
      printf("  mov ecx, eax\n");
      printf("  pop eax\n");
      printf("  sar eax, cl\n");
    }
  /*
   * Unary operations
   */
  | NOT expr {
      printf("  cmp eax, 0\n");
      printf("  sete al\n");
      printf("  movzx eax, al\n");
    }
  | BITNOT expr {
      printf("  not eax\n");
    }
  | MINUS expr %prec STAR {
      printf("  neg eax\n");
    }
  ;

statement:
    lvalue INCREMENT SEMICOLON {
      // lvalue var addr pushed on stack
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
  | if_statement
  ;

while_start:
  WHILE {
    int start_lbl = label_counter;
    label_counter += 2;
    printf(".L%d:\n", start_lbl);
    $$ = start_lbl;
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

if_header:
    IF PAROPEN expr PARCLOSE {
      int else_lbl = label_counter++;
      printf("  cmp eax, 0\n");
      printf("  je .L%d\n", else_lbl);
      $$ = else_lbl; // Cast $$ to num
    }
  ;

if_statement:
    if_header statement %prec IFX {
      printf(".L%d:\n", $1);
    }
  | if_header statement ELSE {
      int exit_lbl = label_counter++;
      printf("  jmp .L%d\n", exit_lbl); // Skip else branch
      printf(".L%d:\n", $1); // Start of else branch
      $<num>$ = exit_lbl;
    }
    statement {
      printf(".L%d:\n", $<num>4);
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
  IDENTIFIER PAROPEN params PARCLOSE BRACEOPEN {
    /* Function header stuff
     * All funcs are flobal in Blang */
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
    /* Reset offsets for new function.
     * Needs to happen *before* params are read.
     * This is executed before every function, but at the end here because it's
     * wrapped to after the last function.
     * We cannot define it at `IDENTIFIER PAROPEN` because it conflicts with
     * other parts of the parser code. */
    current_local_offset = -4;
    current_param_offset = 8;
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
