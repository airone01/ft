%{
#include <stdio.h>
#include "src/yy.h"
#include "src/symtab.h"
#include "src/color.h"
#include "src/asm.h"

/* TODO (BONUS)
 * - switch/case
 * - floating point operator
 * - libb
 * - two additional features
 */
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
%token SEMICOLON COMMA PAROPEN PARCLOSE BRACEOPEN BRACECLOSE ARRCLOSE COMMOPEN COMMCLOSE
%token INCREMENT DECREMENT
%token GOTO COLON

%right EQUAL
%left OR
%left AND
%left BITOR
%left XOR
%left BITAND
%left EQUALS NOTEQUALS
%left LOWER LOWEREQ HIGHER HIGHEREQ
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR DIV MOD
%left NOT BITNOT
%left ARROPEN

%%

program:
  | /* In B/C, there can only be top-level declarations, no expressions. */
    program declaration
  | program func_def
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
    { $$ = 0; }
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
      gen_push_eax();
    } else {
      fprintf(stderr, REDHB" Error: Unknown variable '%s'"CRESET"\n", $1);
    }
  }

expr:
    PAROPEN expr PARCLOSE
  | IDENTIFIER {
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
      gen_push_eax();
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
  | expr PLUS { gen_push_eax(); } expr {
      printf("  pop ebx\n");
      printf("  add eax, ebx\n");
    }
  | expr MINUS { gen_push_eax(); } expr {
      printf("  pop ebx\n");
      printf("  sub ebx, eax\n");
      printf("  mov eax, ebx\n");
    }
  | expr STAR { gen_push_eax(); } expr {
      printf("  pop ebx\n");
      printf("  imul eax, ebx\n");
    }
  | expr DIV { gen_push_eax(); } expr {
      printf("  mov ebx, eax\n"); // Divisor
      printf("  pop eax\n");      // Dividend
      /* "Convert Doubleword to Quadword"
       * Sign-extend `eax` into `edx`. */
      printf("  cdq\n");
      printf("  idiv ebx\n");
    }
  | expr MOD { gen_push_eax(); } expr {
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
  | expr LOWER     { gen_push_eax(); } expr { gen_cmp("setl"); }
  | expr LOWEREQ   { gen_push_eax(); } expr { gen_cmp("setle"); }
  | expr HIGHER    { gen_push_eax(); } expr { gen_cmp("setg"); }
  | expr HIGHEREQ  { gen_push_eax(); } expr { gen_cmp("setge"); }
  | expr EQUALS    { gen_push_eax(); } expr { gen_cmp("sete"); }
  | expr NOTEQUALS { gen_push_eax(); } expr { gen_cmp("setne"); }
  /*
   * Bitwise comparisons
   */
  | expr BITAND { gen_push_eax(); } expr { gen_bit_cmp("and"); }
  | expr BITOR  { gen_push_eax(); } expr { gen_bit_cmp("or"); }
  | expr XOR    { gen_push_eax(); } expr { gen_bit_cmp("xor"); }
  /*
   * Bit shifts
   */
  | expr LSHIFT { gen_push_eax(); } expr { gen_shift("shl"); }
  | expr RSHIFT { gen_push_eax(); } expr { gen_shift("sar"); }
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
  /*
   * Pre/post increment
   */
  | lvalue INCREMENT {
      printf("  pop edx\n");
      printf("  mov eax, [edx]\n");
      printf("  inc dword ptr [edx]\n");
    }
  | lvalue DECREMENT {
      printf("  pop edx\n");
      printf("  mov eax, [edx]\n");
      printf("  dec dword ptr [edx]\n");
    }
  | INCREMENT lvalue {
      printf("  pop edx\n");
      printf("  inc dword ptr [edx]\n");
      printf("  mov eax, [edx]\n");
    }
  | DECREMENT lvalue {
      printf("  pop edx\n");
      printf("  dec dword ptr [edx]\n");
      printf("  mov eax, [edx]\n");
    }
  /*
   * Array indexing
   *
   * Separating arr_access from read vs assignment avoids the LR(1) lookahead
   * problem.
   *
   * In more detail: because we don't use an AST and have a lookahead of one
   * token, we cannot know in advance whether in `v[i]`, `i` should be treated
   * as the start of an lvalue or as an expr.
   * In a modern compiler, this problem would not arise because the first pass
   * of the compiler would resolve `v[i]` as a node of array access of `v` at
   * `i`, and later, a type-checker would run through the tree and solve the
   * sideness of `i`.
   * But, again, we don't have the luxury of an AST.
   *
   * The following is the cleanest solution I've found for this.
   * I also emulate the incrent and decrement here for better parity.
   */
  // Read
  | arr_access {
      printf("  mov eax, [eax]\n");
    }
  // Assignment
  | arr_access EQUAL { gen_push_eax(); } expr {
      printf("  pop ebx\n");
      printf("  mov [ebx], eax\n");
    }
  // Increment
  | arr_access INCREMENT {
      printf("  mov edx, eax\n");
      printf("  mov eax, [edx]\n");
      printf("  inc dword ptr [edx]\n");
    }
  // Decrement
  | arr_access DECREMENT {
      printf("  mov edx, eax\n");
      printf("  mov eax, [edx]\n");
      printf("  dec dword ptr [edx]\n");
    }
  ;

statement:
    expr SEMICOLON
  | BRACEOPEN statements_list BRACECLOSE
  | while_statement
  | if_statement
  | RETURN SEMICOLON {
      printf("  leave\n");
      printf("  ret\n");
    }
  | RETURN expr SEMICOLON {
      printf("  leave\n");
      printf("  ret\n");
    }
  | label statement
  | GOTO IDENTIFIER SEMICOLON {
      printf("  jmp .L_%s_%s\n", current_func_name, $2);
      free($2);
    }
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
      gen_push_eax();
      $$ = 1;
    }
  | args_list COMMA expr {
      gen_push_eax();
      $$ = $1 + 1;
    }
  ;

func_def:
  IDENTIFIER PAROPEN params PARCLOSE BRACEOPEN {
    current_func_name = $1;
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

label:
    IDENTIFIER COLON {
      printf(".L_%s_%s:\n", current_func_name, $1);
      free($1);
    }
  ;

arr_access:
    expr ARROPEN { gen_push_eax(); } expr ARRCLOSE {
      printf("  pop ebx\n");
      printf("  lea eax, [ebx + eax*4]\n");
    }
  ;

%%
