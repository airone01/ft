add(a, b) {
  return (a + b);
}

main() {
  extrn add;
  auto fp, res;
  fp = add;
  res = fp(20, 22);
  if (res != 42) return (1);
  return (0);
}
