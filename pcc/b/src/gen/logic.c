#include "gen.h"

/*
 * Locical AND and OR
 *
 * Expected high-level behavior:
 * The expected high-level logic for OR for example is that when the left-hand
 * expression is true, the right-hand should not be evaluated at run-time.
 * For AND, if the left-hand expression is false, the right-hand one should
 * not be evaluated ar run-time either.
 *
 * This poses issues in LR(1), because no AST, you know the drill.
 * But we have our old friend here to save the day. That's right, it's time
 * for a bunch of mid-rules again!
 *
 * What I came up with:
 *
 * `a && b`:
 * - Evaluate `a` to `eax`
 * - If `eax == 0`, jump to `.L_false` (short-circuit, skip `b`)
 * - Otherwise, evaluate `b` to `eax`
 * - Normalize `b` to `0` or `1` with `setne al`, jump over `.L_false` to
 *   `.L_end`
 * - `.L_false:` set `eax = 0`
 *
 * `a || b`:
 * - Evaluate `a` to `eax`
 * - If `eax != 0`, jump to `.L_true` (short-circuit, skip `b`)
 * - Otherwise, evaluate `b` to `eax`
 * - Normalize `b` to `0` or `1` with `setne al`, jump over `.L_true` to
 *   `.L_end`
 * - `.L_true:` set `eax = 1`
 *
 * Basically the same reversed in both cases. Pretty similar to what I've been
 * doing with the if, else, switch, and case statements.
 */

int gen_logi_and_mid(void) {
  int false_lbl = label_counter++;
  label_counter++;
  printf("  cmp eax, 0\n");
  printf("  je .L%d\n", false_lbl);
  return false_lbl;
}

void gen_logi_and(int false_lbl) {
  int end_lbl = false_lbl + 1;
  printf("  cmp eax, 0\n");
  printf("  setne al\n");
  printf("  movzx eax, al\n");
  printf("  jmp .L%d\n", end_lbl);
  printf(".L%d:\n", false_lbl);
  printf("  mov eax, 0\n");
  printf(".L%d:\n", end_lbl);
}

int gen_logi_or_mid() {
  int true_lbl = label_counter++;
  label_counter++;
  printf("  cmp eax, 0\n");
  printf("  jne .L%d\n", true_lbl);
  return true_lbl;
}

void gen_logi_or(int true_lbl) {
  int end_lbl = true_lbl + 1;
  printf("  cmp eax, 0\n");
  printf("  setne al\n");
  printf("  movzx eax, al\n");
  printf("  jmp .L%d\n", end_lbl);
  printf(".L%d:\n", true_lbl);
  printf("  mov eax, 1\n");
  printf(".L%d:\n", end_lbl);
}
