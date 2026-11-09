#include "gen.h"

/**
 * @param way Whether to increment (0) or decrement (1)
 * @param order Whether to `mov` before (0) or after (1) the operation
 */
void gen_lvalue_inc(IncrWay way, IncrOrder order) {
  const char *op = way == Inc ? "inc" : "dec";
  if (order == Pre) {
    printf("  %s dword ptr [eax]\n", op);
    printf("  mov eax, [eax]\n");
  } else {
    printf("  mov edx, eax\n");
    printf("  mov eax, [edx]\n");
    printf("  %s dword ptr [edx]\n", op);
  }
  is_lvalue = 0;
}
