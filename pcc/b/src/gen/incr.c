#include "gen.h"

/**
 * @param way Whether to increment (0) or decrement (1)
 * @param order Whether to `mov` before (0) or after (1) the operation
 */
void gen_incr(IncrWay way, IncrOrder order) {
  const char *op = way == Inc ? "inc" : "dec";
  printf("  pop edx\n");
  if (order == Post)
    printf("  mov eax, [edx]\n");
  printf("  %s dword ptr [edx]\n", op);
  if (order == Pre)
    printf("  mov eax, [edx]\n");
}
