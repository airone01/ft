main() {
  auto a, r;
  a = 1;
  if (a) r = 10; else r = 20;
  if (r != 10) return (1);
  a = 0;
  if (a) r = 10; else r = 20;
  if (r != 20) return (2);
  return (0);
}
