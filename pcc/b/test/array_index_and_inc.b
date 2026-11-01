main() {
  extrn v;
  v[0] = 10;
  v[1] = 20;
  if (v[0] != 10) return (1);
  if (v[1] != 20) return (2);
  v[0]++;
  if (v[0] != 11) return (3);
  v[1]--;
  if (v[1] != 19) return (4);
  return (0);
}
v[10];
