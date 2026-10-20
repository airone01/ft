#define _GNU_SOURCE

#include "c2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *trim_left(char *s) {
  while (*s == ' ' || *s == '\t')
    s++;
  return s;
}

/*
 * @brief Simple peephole code optimization
 *
 * These are code scanning rules:
 * - Remove dead code after unconditional jump or ret (and before next label).
 * - Remove redundant jumps to labels that are following the jump anyway.
 * - Drop the `push eax` and `pop eax` combo, which does nothing.
 * - Simplify `push eax` `pop ebx` combo to `mov ebx, eax`.
 * - Prefer shorthand mathematical instr instead of convoluted ones.
 *   Ex: `mov eax, 0` can be `xor eax, eax`
 *   See https://stackoverflow.com/a/33668295
 * - Drop `add esp, 0`, which does nothing.
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
  for (ssize_t i = 0; i < count; i++) {
    if (!lines[i] || !lines[i][0])
      continue;

    char *s = trim_left(lines[i]);

    // Rule: dead code after jump
    if (strcmp(s, "ret") == 0 || strncmp(s, "jmp ", 4) == 0) {
      for (ssize_t j = i + 1; j < count; j++) {
        char *sj = trim_left(lines[j]);
        if (sj[0] == '.' || strchr(sj, ':') != NULL)
          break;
        lines[j][0] = '\0';
      }
    }

    // Two-instr peephole
    if (i + 1 < count) {
      int next = i + 1;
      while (next < count && !lines[next][0])
        next++;

      if (next < count) {
        char *s_next = trim_left(lines[next]);

        // Rule: drop redundant jump to label that is following anyway
        if (strncmp(s, "jmp ", 4) == 0 && strchr(s_next, ':') != NULL) {
          char target[64], label[64];
          if (sscanf(s, "jmp %63s", target) == 1 &&
              sscanf(s_next, "%63[^:]:", label) == 1) {
            if (strcmp(target, label) == 0) {
              lines[i][0] = '\0';
              continue;
            }
          }
        }

        // Rule: drop `push eax` / `pop eax combo`
        if (strcmp(s, "push eax") == 0 && strcmp(s_next, "pop eax") == 0) {
          lines[i][0] = '\0';
          lines[next][0] = '\0';
          continue;
        }

        // Rule: `push eax` / `pop ebx` becomes `mov ebx, eax`
        if (strcmp(s, "push eax") == 0 && strcmp(s_next, "pop ebx") == 0) {
          free(lines[i]);
          lines[i] = strdup("  mov ebx, eax");
          lines[next][0] = '\0';
          continue;
        }
      }
    }

    // Rules: prefer shorthand mathematical operation
    if (strcmp(s, "mov eax, 0") == 0) {
      free(lines[i]);
      lines[i] = strdup("  xor eax, eax");
    } else if (strcmp(s, "add eax, 1") == 0) {
      free(lines[i]);
      lines[i] = strdup("  inc eax");
    } else if (strcmp(s, "sub eax, 1") == 0) {
      free(lines[i]);
      lines[i] = strdup("  dec eax");
    } else
      // Rule: drop `add esp, 0` which does nothing
      if (strcmp(s, "add esp, 0") == 0)
        lines[i][0] = '\0';
  }

  // Emit survivors
  for (ssize_t i = 0; i < count; i++) {
    if (lines[i][0] != '\0')
      fprintf(out, "%s\n", lines[i]);
    free(lines[i]);
  }
}
