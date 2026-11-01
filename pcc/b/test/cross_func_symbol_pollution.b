func1() {
  auto x;
  x = 10;
}
func2(x) {
  return (x);
}
main() {
  auto r;
  r = func2(42);
  if (r != 42) return (1);
  return (0);
}
