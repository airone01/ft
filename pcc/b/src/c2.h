#ifndef SRC_C2_H
#define SRC_C2_H

#define MAX_LINES 65536

#include <stdio.h>

typedef int(OptiFun1Instr)(int count, const char *s, size_t curr,
                           char *lines[MAX_LINES]);

typedef int(OptiFun2Instr)(int count, const char *s, const char *s_next,
                           size_t curr, size_t next, char *lines[MAX_LINES]);

char *trim_left(char *s);
void optimize_asm(FILE *in, FILE *out);

// Optimizations with lookahead of 1
OptiFun1Instr dead_code_after_jump;

OptiFun2Instr redundant_jump_to_following_label;
OptiFun2Instr redundant_push_pop_eax;
OptiFun2Instr redundant_push_pop_eax_ebx;

// Optimizations with lookahead of 1 (late usage)
OptiFun1Instr add_esp_0;
OptiFun1Instr shorten_add_1;
OptiFun1Instr shorten_sub_1;
OptiFun1Instr xor_eax_eax;

#endif /* SRC_C2_H */
