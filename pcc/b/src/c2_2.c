#include "c2.h"
#include <stdlib.h>
#include <string.h>

/*
 * @brief Remove redundant jumps to labels that are following the jump anyway
 */
int redundant_jump_to_following_label(int count, const char *s,
                                      const char *s_next, size_t curr,
                                      size_t next, char *lines[]) {
  (void)count, (void)next;
  if (strncmp(s, "jmp ", 4) == 0 && strchr(s_next, ':') != NULL) {
    char target[64], label[64];
    if (sscanf(s, "jmp %63s", target) == 1 &&
        sscanf(s_next, "%63[^:]:", label) == 1) {
      if (strcmp(target, label) == 0) {
        lines[curr][0] = '\0';
        return 1;
      }
    }
  }
  return 0;
}

/*
 * @brief Drop the `push eax` and `pop eax` combo, which does nothing
 */
int redundant_push_pop_eax(int count, const char *s, const char *s_next,
                           size_t curr, size_t next, char *lines[]) {
  (void)count;
  if (strcmp(s, "push eax") == 0 && strcmp(s_next, "pop eax") == 0) {
    lines[curr][0] = '\0';
    lines[next][0] = '\0';
    return 1;
  }
  return 0;
}

/*
 * @brief Simplify `push eax` `pop ebx` combo to `mov ebx, eax`.
 */
int redundant_push_pop_eax_ebx(int count, const char *s, const char *s_next,
                               size_t curr, size_t next, char *lines[]) {
  (void)count;
  if (strcmp(s, "push eax") == 0 && strcmp(s_next, "pop ebx") == 0) {
    free(lines[curr]);
    lines[curr] = strdup("  mov ebx, eax");
    lines[next][0] = '\0';
    return 1;
  }
  return 0;
}
