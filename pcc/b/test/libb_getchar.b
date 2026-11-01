main() {
  extrn getchar;
  auto c1, c2, c3, eof;
  c1 = getchar();
  c2 = getchar();
  c3 = getchar();
  eof = getchar();

  if (c1 != 'A') return (1);
  if (c2 != 'B') return (2);
  if (c3 != 'C') return (3);
  if (eof != -1) return (4);

  return (0);
}
