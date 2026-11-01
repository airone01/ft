main() {
  auto x, r;
  x = 2;
  r = 0;
  switch (x) {
    case 1: r = 10; break;
    case 2: r = 20; break;
    case 3: r = 30; break;
    default: r = 99; break;
  }
  if (r != 20) return (1);
  x = 5;
  switch (x) {
    case 1: r = 10; break;
    case 2: r = 20; break;
    default: r = 99; break;
  }
  if (r != 99) return (2);
  return (0);
}
