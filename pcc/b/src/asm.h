#ifndef SRC_ASM_H
#define SRC_ASM_H

void gen_push_eax(void);

void gen_cmp(const char *set_instr);
void gen_bit_cmp(const char *set_instr);
void gen_fcmp(const char *set_instr);

void gen_shift(const char *shift_instr);

#endif /* SRC_ASM_H */
