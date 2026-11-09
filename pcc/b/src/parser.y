%{
#include <stdio.h>
#include "src/yy.h"
#include "src/symtab.h"
#include "src/color.h"
#include "src/gen/gen.h"
%}

%define parse.error verbose
%locations

%union {
  int num;
  char *str;
}

%type <num> opt_num opt_ival_list ival_list
%type <num> args args_list
%type <num> params params_list
%type <num> while_start
%type <num> if_header
%type <num> assign_op

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
%token TOK_GOTO
%token TOK_ASS_ADD TOK_ASS_SUB TOK_ASS_MUL TOK_ASS_DIV TOK_ASS_MOD
%token TOK_ASS_SHL TOK_ASS_SHR TOK_ASS_AND TOK_ASS_OR TOK_ASS_XOR
%token TOK_ASS_EQ TOK_ASS_NEQ TOK_ASS_LT TOK_ASS_LTE TOK_ASS_GT TOK_ASS_GTE

%right TOK_ASSIGN TOK_ASS_ADD TOK_ASS_SUB TOK_ASS_MUL TOK_ASS_DIV TOK_ASS_MOD TOK_ASS_SHL TOK_ASS_SHR TOK_ASS_AND TOK_ASS_OR TOK_ASS_XOR TOK_ASS_EQ TOK_ASS_NEQ TOK_ASS_LT TOK_ASS_LTE TOK_ASS_GT TOK_ASS_GTE
%right TOK_QUES TOK_COL
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
  | program global_def
  | program func_def
  | program TOK_EXTERN extrn_list TOK_SEMI
  ;

global_def:
    /* Vector: name[size] ival, ... */
    TOK_IDENT TOK_LBRACKET opt_num TOK_RBRACKET
      { gen_global_vec_mid($1); }
    opt_ival_list TOK_SEMI
      { gen_global_vec($1, $3, $6); }
  | /* Scalar: name ival, ... */
    TOK_IDENT
      { gen_global_scal_mid($1); }
    opt_ival_list TOK_SEMI
      { gen_global_scal($1, $3); }
  ;

opt_num:
    /* empty: size 0 */ { $$ = 0; }
  | TOK_NUM             { $$ = $1; }
  ;

opt_ival_list:
    /* empty: size 0 */ { $$ = 0; }
  | ival_list           { $$ = $1; }
  ;

ival_list:
    ival                     { $$ = 1; }
  | ival_list TOK_COMMA ival { $$ = $1 + 1; }
  ;

ival:
    TOK_NUM           { gen_ival_num($1); }
  | TOK_MINUS TOK_NUM { gen_ival_mnum($2); }
  | TOK_STR           { gen_ival_str($1); }
  | TOK_IDENT         { gen_ival_ident($1); }
  ;

declarations:
    // TODO: figure out if empty case should be here or not
    // Note: In THEORY it's not a problem but it might be better to move it one
    // level higher. Worse clarity for users but may be more understandable to
    // yacc??? idk
  | declarations declaration
  ;

declaration:
    TOK_AUTO auto_list TOK_SEMI
  | TOK_EXTERN extrn_list TOK_SEMI
  ;

auto_list:
    TOK_IDENT                     { gen_auto($1); }
  | auto_list TOK_COMMA TOK_IDENT { gen_auto_list($3); }
  ;

extrn_list:
    TOK_IDENT                      { add_symbol($1, TYPE_EXTERN); }
  | extrn_list TOK_COMMA TOK_IDENT { add_symbol($3, TYPE_EXTERN); }
  ;

params_list:
    TOK_IDENT                       { add_symbol($1, TYPE_PARAM); }
  | params_list TOK_COMMA TOK_IDENT { add_symbol($3, TYPE_PARAM); }
  ;

params:
    { $$ = 0; }
  | params_list
  ;

statements_list:
  | statements_list statement
  ;

primary_exp:
    TOK_IDENT { gen_lvalue_addr($1); }
  | TOK_NUM   { gen_expr_num($1); is_lvalue = 0; }
  | TOK_STR   { gen_expr_deref($1); is_lvalue = 0; }
  | TOK_LPAREN expr TOK_RPAREN
  ;

postfix_expr:
    primary_exp
  | postfix_expr TOK_LBRACKET  { ensure_rvalue(); gpe(); }
    expr TOK_RBRACKET          { ensure_rvalue(); gen_arr_acc(); }
  | postfix_expr TOK_LPAREN    { ensure_rvalue(); gpe(); }
    args TOK_RPAREN            { gen_func_call($4); }
  | postfix_expr TOK_INCREMENT { gen_lvalue_inc(Inc, Post); }
  | postfix_expr TOK_DECREMENT { gen_lvalue_inc(Dec, Post); }
  ;

unary_expr:
    postfix_expr
  | TOK_INCREMENT unary_expr  { gen_lvalue_inc(Inc, Pre); }
  | TOK_DECREMENT unary_expr  { gen_lvalue_inc(Dec, Pre); }
  /* ref/deref */
  | TOK_STAR unary_expr       { gen_unary_deref(); }
  | TOK_AMPER unary_expr      { gen_unary_addrof(); }
  /* ops */
  | TOK_MINUS unary_expr      { ensure_rvalue(); gen_unary_neg(); }
  | TOK_EXCL unary_expr       { ensure_rvalue(); gen_unary_excl(); }
  | TOK_TILDE unary_expr      { ensure_rvalue(); gen_unary_not(); }
  | TOK_HASH unary_expr       { ensure_rvalue(); gen_hash(); }
  | TOK_HASH_HASH unary_expr  { ensure_rvalue(); gen_hash_hash(); }
  ;

assign_op:
    TOK_ASSIGN  { $$ = OP_ASSIGN; }
  | TOK_ASS_ADD { $$ = OP_ASSIGN_ADD; }
  | TOK_ASS_SUB { $$ = OP_ASSIGN_SUB; }
  | TOK_ASS_MUL { $$ = OP_ASSIGN_MUL; }
  | TOK_ASS_DIV { $$ = OP_ASSIGN_DIV; }
  | TOK_ASS_MOD { $$ = OP_ASSIGN_MOD; }
  | TOK_ASS_SHL { $$ = OP_ASSIGN_SHL; }
  | TOK_ASS_SHR { $$ = OP_ASSIGN_SHR; }
  | TOK_ASS_AND { $$ = OP_ASSIGN_AND; }
  | TOK_ASS_OR  { $$ = OP_ASSIGN_OR; }
  | TOK_ASS_XOR { $$ = OP_ASSIGN_XOR; }
  | TOK_ASS_EQ  { $$ = OP_ASSIGN_EQ; }
  | TOK_ASS_NEQ { $$ = OP_ASSIGN_NEQ; }
  | TOK_ASS_LT  { $$ = OP_ASSIGN_LT; }
  | TOK_ASS_LTE { $$ = OP_ASSIGN_LTE; }
  | TOK_ASS_GT  { $$ = OP_ASSIGN_GT; }
  | TOK_ASS_GTE { $$ = OP_ASSIGN_GTE; }
  ;

expr:
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
    unary_expr
  | unary_expr assign_op { gen_assign_prep(); }
    expr %prec TOK_ASSIGN { ensure_rvalue(); gen_compound_ass($2); }
  /* bin exprs */
  | expr TOK_PLUS   { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_math_plus(); }
  | expr TOK_MINUS  { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_math_minus(); }
  | expr TOK_STAR   { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_math_mult(); }
  | expr TOK_DIV    { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_math_div(); }
  | expr TOK_MOD    { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_math_mod(); }
  | expr TOK_FPLUS  { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_math_fplus(); }
  | expr TOK_FMINUS { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_math_fminus(); }
  | expr TOK_FMULT  { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_math_fmult(); }
  | expr TOK_FDIV   { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_math_fdiv(); }
  | expr TOK_LANGLE { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_cmp("setl"); }
  | expr TOK_LTE    { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_cmp("setle"); }
  | expr TOK_RANGLE { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_cmp("setg"); }
  | expr TOK_GTE    { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_cmp("setge"); }
  | expr TOK_EQ     { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_cmp("sete"); }
  | expr TOK_NEQ    { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_cmp("setne"); }
  | expr TOK_FLT    { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_fcmp("setb"); }
  | expr TOK_FLTE   { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_fcmp("setbe"); }
  | expr TOK_FGT    { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_fcmp("seta"); }
  | expr TOK_FGTE   { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_fcmp("setae"); }
  | expr TOK_FEQ    { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_fcmp("sete"); }
  | expr TOK_FNEQ   { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_fcmp("setne"); }
  | expr TOK_AMPER  { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_bit_cmp("and"); }
  | expr TOK_PIPE   { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_bit_cmp("or"); }
  | expr TOK_CARRET { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_bit_cmp("xor"); }
  | expr TOK_LSHIFT { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_shift("shl"); }
  | expr TOK_RSHIFT { ensure_rvalue(); gpe(); } expr { ensure_rvalue(); gen_shift("sar"); }
  /* inline cond (and ternary) */
  | expr TOK_DBL_AMPER { ensure_rvalue(); $<num>$ = gen_logi_and_mid(); }
    expr               { ensure_rvalue(); gen_logi_and($<num>3); }
  | expr TOK_DBL_PIPE  { ensure_rvalue(); $<num>$ = gen_logi_or_mid(); }
    expr               { ensure_rvalue(); gen_logi_or($<num>3); }
  | expr TOK_QUES      { ensure_rvalue(); $<num>$ = gen_ternary_mid(); }
    expr TOK_COL       { ensure_rvalue(); $<num>$ = gen_ternary_colon($<num>3); }
    expr               { ensure_rvalue(); gen_ternary_end($<num>6); }
  ;

statement:
    TOK_SEMI
  | statement_in_braces
  | statement_expr
  | statement_while
  | statement_if
  | statement_return
  | statement_label
  | statement_goto
  | statement_switch
  | statement_case
  | statement_default
  | statement_break
  ;
statement_in_braces:
    TOK_LBRACE statements_list TOK_RBRACE
  ;

statement_expr:
    expr TOK_SEMI { ensure_rvalue(); }
  ;

statement_while:
    while_start TOK_LPAREN expr TOK_RPAREN { ensure_rvalue(); gen_while_mid($1); }
    statement                              { gen_while($1); }
  ;
while_start:
    TOK_WHILE                              { $$ = gen_while_start(); }
  ;

statement_if:
    if_header statement %prec IFX     { gen_if_prec($1); }
  | if_header statement TOK_ELSE      { $<num>$ = gen_if_mid($1); }
    statement                         { gen_if($<num>4); }
  ;
if_header:
    TOK_IF TOK_LPAREN expr TOK_RPAREN { ensure_rvalue(); $$ = gen_if_hdr(); }
  ;

statement_return:
    TOK_RETURN TOK_SEMI      { gen_ret(); }
  | TOK_RETURN expr TOK_SEMI { ensure_rvalue(); gen_ret(); }
  ;

args:
                             { $$ = 0; }
  | args_list                { $$ = $1; }
  ;
args_list:
    expr                     { ensure_rvalue(); gpe(); $$ = 1; }
  | args_list TOK_COMMA expr { ensure_rvalue(); gpe(); $$ = $1 + 1; }
  ;
func_def:
    TOK_IDENT TOK_LPAREN params TOK_RPAREN TOK_LBRACE { gen_func_def_mid($1); }
    declarations statements_list TOK_RBRACE           { gen_func_def(); }
  ;

statement_label: label statement;
label:
    TOK_IDENT TOK_COL           { gen_lbl($1); }
  ;
statement_goto:
    TOK_GOTO TOK_IDENT TOK_SEMI { gen_goto($2); }
  ;

statement_switch:
    switch_start statement                { gen_switch(); }
  ;
switch_start:
    TOK_SWITCH TOK_LPAREN expr TOK_RPAREN { ensure_rvalue(); gen_switch_start(); }
  ;
statement_case: case_label statement;
case_label:
    TOK_CASE TOK_NUM TOK_COL              { gen_switch_case($2); }
  ;
statement_default: default_label statement;
default_label:
    TOK_DEFAULT TOK_COL                   { gen_switch_default(); }
  ;

statement_break:
    TOK_BREAK TOK_SEMI { gen_break(@1); }
  ;

%%
