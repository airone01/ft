extrn g1, g2, gv;
main() {
  if (g1 != 42) return (1);
  if (g2 != 0) return (2);
  if (gv[0] != 100) return (3);
  if (gv[1] != 200) return (4);
  if (gv[2] != 0) return (5);
  return (0);
}
g1 42;
g2;
gv[5] 100, 200;
