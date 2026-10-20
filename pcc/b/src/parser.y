%{
#include <stdio.h>
#include "src/yy.h"
#include "src/symtab.h"
#include "src/color.h"
#include "src/asm.h"

/* TODO (BONUS)
 * - libb
 * - two additional features
 */
%}

%define parse.error verbose
%locations

%union {
  int num;
  char *str;
}

%type <num> args args_list
%type <num> params params_list
%type <num> while_start
%type <num> if_header

%nonassoc IFX
%nonassoc TOK_ELSE

%token TOK_UNKNOWN
%token TOK_AUTO TOK_EXTERN TOK_WHILE TOK_IF TOK_ELSE TOK_RETURN
%token <str> TOK_IDENT
%token <num> TOK_NUM
%token <str> TOK_STR
%token TOK_SEMI TOK_COMMA TOK_LPAREN TOK_RPAREN TOK_LBRACE TOK_RBRACE TOK_RBRACKET COMMOPEN COMMCLOSE
%token TOK_SWITCH TOK_CASE TOK_DEFAULT TOK_BREAK
%token TOK_INCREMENT TOK_DECREMENT
%token TOK_GOTO TOK_COL

%right TOK_ASSIGN
%left TOK_DBL_PIPE
%left TOK_DBL_AMPER
%left TOK_PIPE
%left TOK_CARRET
%left TOK_AMPER
%left TOK_EQ TOK_FEQ TOK_NEQ TOK_FNEQ
%left TOK_LANGLE TOK_FLT TOK_LTE TOK_FLTE TOK_RANGLE TOK_FGT TOK_GTE TOK_FGTE
%left TOK_LSHIFT TOK_RSHIFT
%left TOK_PLUS TOK_FPLUS TOK_MINUS TOK_FMINUS
%left TOK_STAR TOK_FMULT TOK_DIV TOK_FDIV TOK_MOD
%left TOK_EXCL TOK_TILDE
%left TOK_HASH TOK_HASH_HASH
%left TOK_LBRACKET

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
    TOK_AUTO auto_list TOK_SEMI
  | TOK_EXTERN extrn_list TOK_SEMI
  ;

auto_list:
    TOK_IDENT {
      add_symbol($1, TYPE_AUTO);
      printf("  push 0\n");
    }
  | auto_list TOK_COMMA TOK_IDENT {
      add_symbol($3, TYPE_AUTO);
      printf("  push 0\n");
    }
  ;

extrn_list:
    TOK_IDENT { add_symbol($1, TYPE_EXTERN); }
  | extrn_list TOK_COMMA TOK_IDENT { add_symbol($3, TYPE_EXTERN); }
  ;

params_list:
    TOK_IDENT { add_symbol($1, TYPE_PARAM); }
  | params_list TOK_COMMA TOK_IDENT { add_symbol($3, TYPE_PARAM); }
  ;

params:
    { $$ = 0; }
  | params_list
  ;

statements_list:
  | statements_list statement
  ;

lvalue:
    TOK_IDENT {
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
        fprintf(stderr, "<stdin>:%d:%d: " RED "error:" CRESET " unknown variable '%s'\n",
                @1.first_line, @1.first_column, $1);
      }
    }
  ;

expr:
    TOK_LPAREN expr TOK_RPAREN
  | TOK_IDENT {
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
        fprintf(stderr, "<stdin>: " RED "error:" CRESET " unknown variable '%s'\n", $1);
      }
    }
  | TOK_NUM { printf("  mov eax, %d\n", $1); }
  // Address-of
  | TOK_AMPER lvalue %prec TOK_EXCL { printf("  pop eax\n"); }
  // Dereference
  | TOK_STAR expr %prec TOK_EXCL { printf("  mov eax, [eax]\n"); }
  | TOK_STR {
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
  | TOK_IDENT TOK_LPAREN {
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
    TOK_RPAREN {
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
  | lvalue TOK_ASSIGN expr {
      /* Assignment as expression
       * (eg `var = ...` in if condition) */
      printf("  pop ebx\n");
      printf("  mov [ebx], eax\n");
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
   * Math operations
   */
  | expr TOK_PLUS { gen_push_eax(); } expr {
      printf("  pop ebx\n");
      printf("  add eax, ebx\n");
    }
  | expr TOK_MINUS { gen_push_eax(); } expr {
      printf("  pop ebx\n");
      printf("  sub ebx, eax\n");
      printf("  mov eax, ebx\n");
    }
  | expr TOK_STAR { gen_push_eax(); } expr {
      printf("  pop ebx\n");
      printf("  imul eax, ebx\n");
    }
  | expr TOK_DIV { gen_push_eax(); } expr {
      printf("  mov ebx, eax\n"); // Divisor
      printf("  pop eax\n");      // Dividend
      /* "Convert Doubleword to Quadword"
       * Sign-extend `eax` into `edx`. */
      printf("  cdq\n");
      printf("  idiv ebx\n");
    }
  | expr TOK_MOD { gen_push_eax(); } expr {
      printf("  mov ebx, eax\n"); // Divisor
      printf("  pop eax\n");      // Dividend
      /* "Convert Doubleword to Quadword"
       * Sign-extend `eax` into `edx`. */
      printf("  cdq\n");
      printf("  idiv ebx\n");
      printf("  mov eax, edx\n"); // Remainder in edx
    }
  /*
   * Math operations on floating-point numbers
   *
   * The `ss` prefix at the end of instructions like `addss` stands for
   * 'Scalar Single-precision' (to contrast with `ps` for 'Packed Single',
   * `sd` for 'Scalar Double', and `pd` for 'Packed Double').
   */
  | expr TOK_FPLUS { gen_push_eax(); } expr {
      printf("  pop ebx\n");
      printf("  movd xmm1, ebx\n");
      printf("  movd xmm0, eax\n");
      printf("  addss xmm1, xmm0\n");
      printf("  movd eax, xmm1\n");
    }
  // This one is special. Since the IEEE-754 value is in `eax` already, we just
  // need to invert the sign bit
  | expr TOK_FMINUS { gen_push_eax(); } expr { printf("  xor eax, 0x80000000\n"); }
  | expr TOK_FMULT { gen_push_eax(); } expr {
      printf("  pop ebx\n");
      printf("  movd xmm1, ebx\n");
      printf("  movd xmm0, eax\n");
      printf("  mulss xmm1, xmm0\n");
      printf("  movd eax, xmm1\n");
    }
  | expr TOK_FDIV { gen_push_eax(); } expr {
      printf("  pop ebx\n");
      printf("  movd xmm1, ebx\n");
      printf("  movd xmm0, eax\n");
      printf("  divss xmm1, xmm0\n");
      printf("  movd eax, xmm1\n");
    }
  | TOK_HASH expr {
      /* CVTSI2SS is hard to swallow but it converts a signed integer into a
       * scalar single-precision floating-point value (stored here into xmm0's
       * low 32 bits).
       * https://intel.github.io/SDM/instruction/CVTSI2SS.html
       */
      printf("  cvtsi2ss xmm0, eax\n");
      printf("  movd eax, xmm0\n");
    }
  | TOK_HASH_HASH expr {
      /* The inverse from above.
       * https://intel.github.io/SDM/instruction/CVTTSS2SI.html */
      printf("  movd xmm0, eax\n");
      printf("  cvttss2si eax, xmm0\n");
    }
  /*
   * Number comparisons
   */
  | expr TOK_LANGLE { gen_push_eax(); } expr { gen_cmp("setl"); }
  | expr TOK_LTE    { gen_push_eax(); } expr { gen_cmp("setle"); }
  | expr TOK_RANGLE { gen_push_eax(); } expr { gen_cmp("setg"); }
  | expr TOK_GTE    { gen_push_eax(); } expr { gen_cmp("setge"); }
  | expr TOK_EQ     { gen_push_eax(); } expr { gen_cmp("sete"); }
  | expr TOK_NEQ    { gen_push_eax(); } expr { gen_cmp("setne"); }
  /*
   * Floating-point number comparisons
   */
  | expr TOK_FLT  { gen_push_eax(); } expr { gen_fcmp("setb"); }
  | expr TOK_FLTE { gen_push_eax(); } expr { gen_fcmp("setbe"); }
  | expr TOK_FGT  { gen_push_eax(); } expr { gen_fcmp("seta"); }
  | expr TOK_FGTE { gen_push_eax(); } expr { gen_fcmp("setae"); }
  | expr TOK_FEQ  { gen_push_eax(); } expr { gen_fcmp("sete"); }
  | expr TOK_FNEQ { gen_push_eax(); } expr { gen_fcmp("setne"); }
  /*
   * Bitwise comparisons
   */
  | expr TOK_AMPER  { gen_push_eax(); } expr { gen_bit_cmp("and"); }
  | expr TOK_PIPE   { gen_push_eax(); } expr { gen_bit_cmp("or"); }
  | expr TOK_CARRET { gen_push_eax(); } expr { gen_bit_cmp("xor"); }
  /*
   * Bit shifts
   */
  | expr TOK_LSHIFT { gen_push_eax(); } expr { gen_shift("shl"); }
  | expr TOK_RSHIFT { gen_push_eax(); } expr { gen_shift("sar"); }
  /*
   * Unary operations
   */
  | TOK_EXCL expr {
      printf("  cmp eax, 0\n");
      printf("  sete al\n");
      printf("  movzx eax, al\n");
    }
  | TOK_TILDE expr {
      printf("  not eax\n");
    }
  | TOK_MINUS expr %prec TOK_STAR {
      printf("  neg eax\n");
    }
  /*
   * Pre/post increment
   */
  | lvalue TOK_INCREMENT {
      printf("  pop edx\n");
      printf("  mov eax, [edx]\n");
      printf("  inc dword ptr [edx]\n");
    }
  | lvalue TOK_DECREMENT {
      printf("  pop edx\n");
      printf("  mov eax, [edx]\n");
      printf("  dec dword ptr [edx]\n");
    }
  | TOK_INCREMENT lvalue {
      printf("  pop edx\n");
      printf("  inc dword ptr [edx]\n");
      printf("  mov eax, [edx]\n");
    }
  | TOK_DECREMENT lvalue {
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
  | arr_access TOK_ASSIGN { gen_push_eax(); } expr {
      printf("  pop ebx\n");
      printf("  mov [ebx], eax\n");
    }
  // Increment
  | arr_access TOK_INCREMENT {
      printf("  mov edx, eax\n");
      printf("  mov eax, [edx]\n");
      printf("  inc dword ptr [edx]\n");
    }
  // Decrement
  | arr_access TOK_DECREMENT {
      printf("  mov edx, eax\n");
      printf("  mov eax, [edx]\n");
      printf("  dec dword ptr [edx]\n");
    }
  /* Locical AND and OR
   *
   * Expected high-level behavior:
   * The expected high-level logic for OR for example is that when the left-hand
   * expression is true, the right-hand should not be evaluated at run-time.
   * For AND, if the left-hand expression is false, the right-hand one should
   * not be evaluated ar run-time either.
   *
   * This poses issues in LR(1), because no AST, you know the drill.
   * But we have our old friend here to save the day. That's right, it's time
   * for a bunch of mid-rules again!
   *
   * What I came up with:
   *
   * `a && b`:
   * - Evaluate `a` to `eax`
   * - If `eax == 0`, jump to `.L_false` (short-circuit, skip `b`)
   * - Otherwise, evaluate `b` to `eax`
   * - Normalize `b` to `0` or `1` with `setne al`, jump over `.L_false` to
   *   `.L_end`
   * - `.L_false:` set `eax = 0`
   *
   * `a || b`:
   * - Evaluate `a` to `eax`
   * - If `eax != 0`, jump to `.L_true` (short-circuit, skip `b`)
   * - Otherwise, evaluate `b` to `eax`
   * - Normalize `b` to `0` or `1` with `setne al`, jump over `.L_true` to
   *   `.L_end`
   * - `.L_true:` set `eax = 1`
   *
   * Basically the same reversed in both cases. Pretty similar to what I've been
   * doing with the if, else, switch, and case statements.
   */
  | expr TOK_DBL_AMPER {
      int false_lbl = label_counter++;
      label_counter++;
      printf("  cmp eax, 0\n");
      printf("  je .L%d\n", false_lbl);
      $<num>$ = false_lbl;
    } expr {
      int false_lbl = $<num>3;
      int end_lbl = false_lbl + 1;
      printf("  cmp eax, 0\n");
      printf("  setne al\n");
      printf("  movzx eax, al\n");
      printf("  jmp .L%d\n", end_lbl);
      printf(".L%d:\n", false_lbl);
      printf("  mov eax, 0\n");
      printf(".L%d:\n", end_lbl);
    }
  | expr TOK_DBL_PIPE {
      int true_lbl = label_counter++;
      label_counter++;
      printf("  cmp eax, 0\n");
      printf("  jne .L%d\n", true_lbl);
      $<num>$ = true_lbl;
    } expr {
      int true_lbl = $<num>3;
      int end_lbl= true_lbl + 1;
      printf("  cmp eax, 0\n");
      printf("  setne al\n");
      printf("  movzx eax, al\n");
      printf("  jmp .L%d\n", end_lbl);
      printf(".L%d:\n", true_lbl);
      printf("  mov eax, 1\n");
      printf(".L%d:\n", end_lbl);
    }
  ;

statement:
    expr TOK_SEMI
  | TOK_LBRACE statements_list TOK_RBRACE
  | while_statement
  | if_statement
  | TOK_RETURN TOK_SEMI {
      printf("  leave\n");
      printf("  ret\n");
    }
  | TOK_RETURN expr TOK_SEMI {
      printf("  leave\n");
      printf("  ret\n");
    }
  | label statement
  | TOK_GOTO TOK_IDENT TOK_SEMI {
      printf("  jmp .L_%s_%s\n", current_func_name, $2);
      free($2);
    }
  | case_label statement
  | default_label statement
  | TOK_BREAK TOK_SEMI {
      if (switch_depth == 0) {
        fprintf(stderr, "<stdin>:%d:%d: " YEL "warning:" CRESET " 'break' "
                "outside of a switch statement\n",
                @1.first_line, @1.first_column);
        fprintf(stderr, "<stdin>:%d:%d: " CYN "note:" CRESET " if this was used"
                " in a loop, note that it is not implemented yet and will break"
                CRESET "\n",
                @1.first_line, @1.first_column);
      } else
        printf("  jmp .L%d\n", switch_stack[switch_depth - 1].end_lbl);
    }
  | switch_statement
  ;

while_start:
  TOK_WHILE {
    int start_lbl = label_counter;
    label_counter += 2;
    printf(".L%d:\n", start_lbl);
    $$ = start_lbl;
  }

while_statement:
  while_start TOK_LPAREN expr TOK_RPAREN {
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
    TOK_IF TOK_LPAREN expr TOK_RPAREN {
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
  | if_header statement TOK_ELSE {
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
  | args_list TOK_COMMA expr {
      gen_push_eax();
      $$ = $1 + 1;
    }
  ;

func_def:
  TOK_IDENT TOK_LPAREN params TOK_RPAREN TOK_LBRACE {
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
  TOK_RBRACE {
    printf("  leave\n");
    printf("  ret\n");
    /* Reset offsets for new function.
     * Needs to happen *before* params are read.
     * This is executed before every function, but at the end here because it's
     * wrapped to after the last function.
     * We cannot define it at `TOK_IDENT TOK_LPAREN` because it conflicts with
     * other parts of the parser code. */
    current_local_offset = -4;
    current_param_offset = 8;
  }
  ;

label:
    TOK_IDENT TOK_COL {
      printf(".L_%s_%s:\n", current_func_name, $1);
      free($1);
    }
  ;

arr_access:
    expr TOK_LBRACKET { gen_push_eax(); } expr TOK_RBRACKET {
      printf("  pop ebx\n");
      printf("  lea eax, [ebx + eax*4]\n");
    }
  ;

case_label:
    TOK_CASE TOK_NUM TOK_COL {
      int lbl = label_counter++;
      add_case($2, lbl);
      printf(".L%d:\n", lbl);
    }
  ;

default_label:
    TOK_DEFAULT TOK_COL {
      int lbl = label_counter++;
      if (switch_depth > 0)
        switch_stack[switch_depth - 1].default_lbl = lbl;
      printf(".L%d:\n", lbl);
    }
  ;

switch_start:
    TOK_SWITCH TOK_LPAREN expr TOK_RPAREN {
      int dispatch_lbl = label_counter++;
      int end_lbl = label_counter++;
      push_switch(dispatch_lbl, end_lbl);
      gen_push_eax();
      printf("  jmp .L%d\n", dispatch_lbl);
    }
  ;

switch_statement:
    switch_start statement {
      SwitchContext *sc = &switch_stack[switch_depth - 1];
      // Fallthrough protection for end of body
      printf("  jmp .L%d\n", sc->end_lbl);
      printf(".L%d:\n", sc->dispatch_lbl);

      // Emit comps
      for (int i = 0; i < sc->case_count; i++) {
        printf("  cmp dword ptr [esp], %d\n", sc->cases[i].val);
        printf("  je .L%d\n", sc->cases[i].lbl);
      }

      if (sc->default_lbl)
        printf("  jmp .L%d\n", sc->default_lbl);
      printf(".L%d:\n", sc->end_lbl);
      printf("  add esp, 4\n");
      pop_switch();
    }

%%
