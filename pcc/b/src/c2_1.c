#include "c2.h"
#include <stdlib.h>
#include <string.h>

/*
 * @brief Remove dead code after unconditional jump or ret (and before next
 * label)
 */
int dead_code_after_jump(int count, const char *s, size_t curr, char *lines[]) {
  if (strcmp(s, "ret") == 0 || strncmp(s, "jmp ", 4) == 0) {
    for (size_t j = curr + 1; (int)j < count; j++) {
      char *sj = trim_left(lines[j]);
      if (sj[0] == '.' || strchr(sj, ':') != NULL)
        break;
      lines[j][0] = '\0';
    }
  }

  return 0;
}

/*
 * @brief Use `xor` to nullify `eax`
 * @see https://stackoverflow.com/a/33668295
 */
int xor_eax_eax(int count, const char *s, size_t curr, char *lines[]) {
  (void)count;

  if (strcmp(s, "mov eax, 0") == 0) {
    free(lines[curr]);
    lines[curr] = strdup("  xor eax, eax");
    return 1;
  }
  return 0;
}

/*
 * @brief Shorten `add eax, 1` to `inc eax`
 */
int shorten_add_1(int count, const char *s, size_t curr, char *lines[]) {
  (void)count;

  if (strcmp(s, "add eax, 1") == 0) {
    free(lines[curr]);
    lines[curr] = strdup("  inc eax");
    return 1;
  }
  return 0;
}

/*
 * @brief Shorten `sub eax, 1` to `dec eax`
 */
int shorten_sub_1(int count, const char *s, size_t curr, char *lines[]) {
  (void)count;

  if (strcmp(s, "sub eax, 1") == 0) {
    free(lines[curr]);
    lines[curr] = strdup("  dec eax");
    return 1;
  }
  return 0;
}

/*
 * @brief Drop `add esp, 0`, which does nothing.
 */
int add_esp_0(int count, const char *s, size_t curr, char *lines[]) {
  (void)count;

  if (strcmp(s, "add esp, 0") == 0) {
    lines[curr][0] = '\0';
    return 1;
  }
  return 0;
}
