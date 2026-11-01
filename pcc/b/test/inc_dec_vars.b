main() {
  auto x, y;
  x = 10;
  y = x++;
  if (y != 10) return (1);
  if (x != 11) return (2);
  y = ++x;
  if (y != 12) return (3);
  if (x != 12) return (4);
  y = x--;
  if (y != 12) return (5);
  if (x != 11) return (6);
  y = --x;
  if (y != 10) return (7);
  if (x != 10) return (8);
  return (0);
}
