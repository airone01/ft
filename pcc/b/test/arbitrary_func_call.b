add1(x) { return (x + 1); }
add2(x) { return (x + 2); }
get_fn() { return (add1); }
v[2];

main() {
  auto pptr, ptr;

  /* 1. Ternary expression as callee */
  if ((1 ? add1 : add2)(10) != 11) return (1);
  if ((0 ? add1 : add2)(10) != 12) return (2);

  /* 2. Vector indexing as callee */
  v[0] = add1;
  v[1] = add2;
  if (v[0](20) != 21) return (3);
  if (v[1](20) != 22) return (4);

  /* 3. Chained function call (calling returned function pointer) */
  if (get_fn()(30) != 31) return (5);

  /* 4. Dereferencing pointer-to-function-pointer */
  ptr = add2;
  pptr = &ptr;
  if ((*pptr)(40) != 42) return (6);

  return (0);
}
