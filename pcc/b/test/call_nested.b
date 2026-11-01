add(a, b) { return (a + b); }
mul(a, b) { return (a * b); }
main() {
  auto r;
  r = add(mul(2, 3), mul(4, 5));
  if (r != 26) return (1);
  return (0);
}
