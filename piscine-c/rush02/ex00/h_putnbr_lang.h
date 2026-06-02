
#ifndef H_PUTNBR_LANG_H
#define H_PUTNBR_LANG_H

#include "h_rush.h"

// QTY
void putnbr_lang_3x_hundreds(struct s_lang_args args, int three_x);
void putnbr_lang_3x_tens(struct s_lang_args args, int three_x);
void putnbr_lang_3x_units(struct s_lang_args args, int three_x);
// Extra
void putnbr_lang_3x_specials(struct s_lang_args args, int three_x);
void putnbr_lang_3x_qty(struct s_lang_args args, int three_x);
// Final form
void putnbr_lang(struct s_lang_args args);
int get_3x(struct s_lang_args args);

#endif
