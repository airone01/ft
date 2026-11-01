main() {
  extrn char;
  auto s;
  s = "ABCD";
  if (char(s, 0) != 'A') return (1);
  if (char(s, 1) != 'B') return (2);
  if (char(s, 2) != 'C') return (3);
  if (char(s, 3) != 'D') return (4);
  return (0);
}
