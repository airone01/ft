#ifndef SRC_GEN_GEN_H
#define SRC_GEN_GEN_H

#define gpe gen_push_eax

// Shamelessly stolen from  y.tab.h
#if !defined YYLTYPE && !defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
#define YYLTYPE_IS_DECLARED 1
#define YYLTYPE_IS_TRIVIAL 1
#endif

#include "../color.h"
#include "../symtab.h"
#include <stdio.h>
#include <stdlib.h>

void gen_lvalue(char *name, YYLTYPE _1);
void gen_push_eax(void);

/*
 * Comparisons
 */
void gen_cmp(const char *set_instr);
void gen_bit_cmp(const char *set_instr);
void gen_fcmp(const char *set_instr);

/*
 * Math operations
 */
void gen_math_plus(void);
void gen_math_minus(void);
void gen_math_mult(void);
void gen_math_div(void);
void gen_math_mod(void);

/*
 * Math operations on floating-point numbers
 *
 * The `ss` prefix at the end of instructions like `addss` stands for
 * 'Scalar Single-precision' (to contrast with `ps` for 'Packed Single',
 * `sd` for 'Scalar Double', and `pd` for 'Packed Double').
 */
void gen_math_fplus(void);
void gen_math_fminus(void);
void gen_math_fmult(void);
void gen_math_fdiv(void);
void gen_math_fmod(void);

/*
 * Bit-shifting
 */
void gen_shift(const char *shift_instr);

/*
 * Unary operations
 */
void gen_unary_excl(void);
void gen_unary_not(void);
void gen_unary_neg(void);

/*
 * Pre/post increment
 */
typedef enum {
  Inc,
  Dec,
} IncrWay;
typedef enum {
  Post,
  Pre,
} IncrOrder;
void gen_incr(IncrWay way, IncrOrder order);

/*
 * Array indexing
 */
void gen_arr_read(void);
void gen_arr_write(void);
void gen_arr_inc(void);
void gen_arr_dec(void);
void gen_arr_acc(void);

/*
 * Locical AND and OR
 */
int gen_logi_and_mid(void);
void gen_logi_and(int false_lbl);
int gen_logi_or_mid(void);
void gen_logi_or(int true_lbl);

/*
 * Return in statement
 */
void gen_ret(void);

/*
 * GOTOs and labels
 */
void gen_goto(char *lbl);
void gen_lbl(char *lbl);

/*
 * Hash
 */
void gen_hash(void);
void gen_hash_hash(void);

/*
 * Globals
 */
void gen_global_vec_mid(const char *lbl);
void gen_global_vec(char *name, int size, int count);
void gen_global_scal_mid(const char *lbl);
void gen_global_scal(char *name, int count);

/*
 * Ival
 */
void gen_ival_num(int num);
void gen_ival_mnum(int num);
void gen_ival_str(char *str);
void gen_ival_ident(char *str);

/*
 * Auto
 */
void gen_auto(const char *name);
void gen_auto_list(const char *name);

/*
 * Expr
 */
void gen_expr_ident(char *name);
void gen_expr_num(int num);
void gen_expr_addrof(void);
void gen_expr_deref_expr(void);
void gen_expr_deref(const char *name);
void gen_expr_ass(void);

/*
 * Func
 */
void gen_func_call_mid(char *name);
void gen_func_call(int argc);
void gen_func_def_mid(char *fname);
void gen_func_def(void);

/*
 * Switch
 */
void gen_switch(void);
void gen_switch_start(void);
void gen_switch_case(int num);
void gen_switch_default(void);

/*
 * Break
 */
void gen_break(YYLTYPE _1);

/*
 * While
 */
void gen_while_mid(int start_lbl);
void gen_while(int start_lbl);
int gen_while_start(void);

/*
 * If
 */
void gen_if_prec(int else_lbl);
int gen_if_mid(int else_lbl);
void gen_if(int exit_lbl);
int gen_if_hdr(void);

#endif /* SRC_GEN_GEN_H */
