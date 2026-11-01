main() {
  auto a, b, r;
  a = 0;
  b = 1;
  r = 0;
  if (a)
    if (b) r = 1;
    else r = 2;
  else
    r = 3;
  if (r != 3) return (1);
  return (0);
}
