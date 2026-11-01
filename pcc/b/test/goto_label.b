main() {
  auto x;
  x = 0;
  goto skip;
  x = 100;
skip:
  if (x != 0) return (1);
  return (0);
}
