#include "gen.h"

void gen_expr_ident(char *name) {
  /* Load value where pointed to by variable. Meaning simply loading a variable.
   */
  Symbol *sym = get_symbol(name);
  if (!sym || sym->type == TYPE_EXTERN) {
    printf("  lea eax, \"%s\"\n", name);
  } else if (sym->type == TYPE_AUTO) {
    printf("  lea eax, [ebp %d]\n", sym->offset);
  } else if (sym->type == TYPE_PARAM) {
    printf("  lea eax, [ebp + %d]\n", sym->offset);
  }
  printf("  mov eax, [eax]\n");
}

void gen_expr_num(int num) { printf("  mov eax, %d\n", num); }

void gen_expr_addrof(void) { printf("  pop eax\n"); }

void gen_expr_deref_expr(void) { printf("  mov eax, [eax]\n"); }

void gen_expr_deref(const char *name) {
  /* Pretty cool stuff: creates an inline read-only section with the string,
   * and then load its pointer into `eax` ofc */
  printf("  .section .rodata\n");
  printf("  .LC%d:\n", string_counter);
  printf("    .long .LC%d+4\n", string_counter);
  printf("    .string %s\n", name);
  printf("  .text\n");
  printf("  mov eax, .LC%d\n", string_counter);
  string_counter++;
}

void gen_expr_ass(void) {
  /* Assignment as expression
   * (eg `var = ...` in if condition) */
  printf("  pop ebx\n");
  printf("  mov [ebx], eax\n");
}

void gen_compound_ass(AssignOp op) {
  printf("  pop ebx\n");
  switch (op) {
  case OP_ASSIGN:
    printf("  mov [ebx], eax\n");
    break;
  case OP_ASSIGN_ADD:
    printf("  add [ebx], eax\n");
    printf("  mov eax, [ebx]\n");
    break;
  case OP_ASSIGN_SUB:
    printf("  sub [ebx], eax\n");
    printf("  mov eax, [ebx]\n");
    break;
  case OP_ASSIGN_MUL:
    printf("  imul eax, [ebx]\n");
    printf("  mov [ebx], eax\n");
    break;
  case OP_ASSIGN_DIV:
    printf("  mov ecx, eax\n");
    printf("  mov eax, [ebx]\n");
    printf("  cdq\n");
    printf("  idiv ecx\n");
    printf("  mov [ebx], eax\n");
    break;
  case OP_ASSIGN_MOD:
    printf("  mov ecx, eax\n");
    printf("  mov eax, [ebx]\n");
    printf("  cdq\n");
    printf("  idiv ecx\n");
    printf("  mov eax, edx\n");
    printf("  mov [ebx], eax\n");
    break;
  case OP_ASSIGN_AND:
    printf("  and [ebx], eax\n");
    printf("  mov eax, [ebx]\n");
    break;
  case OP_ASSIGN_OR:
    printf("  or [ebx], eax\n");
    printf("  mov eax, [ebx]\n");
    break;
  case OP_ASSIGN_XOR:
    printf("  xor [ebx], eax\n");
    printf("  mov eax, [ebx]\n");
    break;
  case OP_ASSIGN_SHL:
    printf("  mov ecx, eax\n");
    printf("  shl dword ptr [ebx], cl\n");
    printf("  mov eax, [ebx]\n");
    break;
  case OP_ASSIGN_SHR:
    printf("  mov ecx, eax\n");
    printf("  sar dword ptr [ebx], cl\n");
    printf("  mov eax, [ebx]\n");
    break;
  case OP_ASSIGN_EQ:
    printf("  cmp [ebx], eax\n");
    printf("  sete al\n");
    printf("  movzx eax, al\n");
    printf("  mov [ebx], eax\n");
    break;
  case OP_ASSIGN_NEQ:
    printf("  cmp [ebx], eax\n");
    printf("  setne al\n");
    printf("  movzx eax, al\n");
    printf("  mov [ebx], eax\n");
    break;
  case OP_ASSIGN_LT:
    printf("  cmp [ebx], eax\n");
    printf("  setl al\n");
    printf("  movzx eax, al\n");
    printf("  mov [ebx], eax\n");
    break;
  case OP_ASSIGN_LTE:
    printf("  cmp [ebx], eax\n");
    printf("  setle al\n");
    printf("  movzx eax, al\n");
    printf("  mov [ebx], eax\n");
    break;
  case OP_ASSIGN_GT:
    printf("  cmp [ebx], eax\n");
    printf("  setg al\n");
    printf("  movzx eax, al\n");
    printf("  mov [ebx], eax\n");
    break;
  case OP_ASSIGN_GTE:
    printf("  cmp [ebx], eax\n");
    printf("  setge al\n");
    printf("  movzx eax, al\n");
    printf("  mov [ebx], eax\n");
    break;
  }
}
