main() {
  auto a, b;
  a = 42;
  b = -a;
  if (b != -42) return (1);
  if (-b != 42) return (2);
  if (-(a - 2) != -40) return (3);
  if (-0 != 0) return (4);
  return (0);
}
