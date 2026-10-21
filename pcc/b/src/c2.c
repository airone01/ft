#define _GNU_SOURCE

#include "c2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *trim_left(char *s) {
  while (*s == ' ' || *s == '\t')
    s++;
  return s;
}

/*
 * Function definitions in `c2.h`.
 * @returns 1 on `continue`, 0 on nothing
 */
static OptiFun1Instr *opti1[] = {dead_code_after_jump};
static OptiFun2Instr *opti2[] = {
    redundant_jump_to_following_label,
    redundant_push_pop_eax,
    redundant_push_pop_eax_ebx,
};
static OptiFun1Instr *opti1_late[] = {shorten_add_1, shorten_sub_1, add_esp_0,
                                      xor_eax_eax};

/*
 * @brief Simple peephole three-pass code optimization
 */
void optimize_asm(FILE *in, FILE *out) {
  char *lines[MAX_LINES];
  int count = 0;
  char buf[512];

  // Read ASM into mem
  while (fgets(buf, sizeof(buf), in) && count < MAX_LINES) {
    buf[strcspn(buf, "\n\r")] = '\0';
    lines[count++] = strdup(buf);
  }

  // Peephole
  for (int i = 0; i < count; i++) {
    if (!lines[i] || !lines[i][0])
      continue;

    char *s = trim_left(lines[i]);

    for (int oi = 0; oi < (int)(sizeof(opti1) / sizeof(OptiFun1Instr *));
         oi++) {
      int ret = (opti1[oi])(count, s, i, lines);
      if (ret == 1)
        goto next_line;
    }

    // Two-instr peephole
    if (i + 1 < count) {
      int next = i + 1;
      while (next < count && !lines[next][0])
        next++;

      if (next < count) {
        char *s_next = trim_left(lines[next]);

        for (int oi = 0; oi < (int)(sizeof(opti2) / sizeof(OptiFun2Instr *));
             oi++) {
          int ret = (opti2[oi])(count, s, s_next, i, next, lines);
          if (ret == 1)
            goto next_line;
        }
      }
    }

    for (int oi = 0; oi < (int)(sizeof(opti1_late) / sizeof(OptiFun1Instr *));
         oi++) {
      int ret = (opti1_late[oi])(count, s, i, lines);
      if (ret == 1)
        goto next_line;
    }

  next_line:;
  }

  // Emit survivors
  for (int i = 0; i < count; i++) {
    if (lines[i][0] != '\0')
      fprintf(out, "%s\n", lines[i]);
    free(lines[i]);
  }
}
