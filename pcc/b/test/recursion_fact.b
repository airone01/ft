fact(n) {
  if (n <= 1) return (1);
  return (n * fact(n - 1));
}
main() {
  auto r;
  r = fact(5);
  if (r != 120) return (1);
  return (0);
}
