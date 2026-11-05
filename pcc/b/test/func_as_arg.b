add(a, b) {
  return (a + b);
}

sub(a, b) {
  return (a - b);
}

mul(a, b) {
  return (a * b);
}

apply2(fn, a, b) {
  return (fn(a, b));
}

apply_chain(f, g, x) {
  return (f(g(x)));
}

double(x) {
  return (x * 2);
}

add_five(x) {
  return (x + 5);
}

pass_through(fn, x) {
  return (pass_through_helper(fn, x));
}

pass_through_helper(fn, x) {
  return (fn(x));
}

rec_sum(self, n) {
  if (n <= 0) return (0);
  return (n + self(self, n - 1));
}

main() {
  auto r;

  /* 1. Direct function passed as argument */
  r = apply2(add, 15, 27);
  if (r != 42) return (1);

  /* 2. Function passed to apply2 */
  r = apply2(sub, 50, 8);
  if (r != 42) return (2);

  r = apply2(mul, 6, 7);
  if (r != 42) return (3);

  /* 3. Chained higher-order functions: f(g(x)) */
  r = apply_chain(double, add_five, 16); /* (16 + 5) * 2 = 42 */
  if (r != 42) return (4);

  /* 4. Multi-level argument forwarding */
  r = pass_through(double, 21);
  if (r != 42) return (5);

  /* 5. Function passing itself recursively */
  r = rec_sum(rec_sum, 5); /* 5 + 4 + 3 + 2 + 1 = 15 */
  if (r != 15) return (6);

  return (0);
}
