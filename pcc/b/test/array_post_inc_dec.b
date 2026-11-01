main() {
  extrn v;
  auto val;
  v[0] = 10;
  v[1] = 20;

  val = v[0]++;
  if (val != 10) return (1);
  if (v[0] != 11) return (2);

  val = v[1]--;
  if (val != 20) return (3);
  if (v[1] != 19) return (4);

  return (0);
}
v[5];
