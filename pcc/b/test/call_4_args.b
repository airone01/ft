f4(a, b, c, d) { return (a * 1000 + b * 100 + c * 10 + d); }
main() {
  if (f4(1, 2, 3, 4) != 1234) return (1);
  return (0);
}
