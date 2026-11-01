main() {
  auto a, b, c, d;
  a = b = c = 42;
  if (a != 42) return (1);
  if (b != 42) return (2);
  if (c != 42) return (3);

  if ((d = a + 8) != 50) return (4);
  if (d != 50) return (5);

  return (0);
}
