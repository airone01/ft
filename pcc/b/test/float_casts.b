main() {
  auto i, f, i2;
  i = 42;
  f = # i;
  /* 42.0 in IEEE-754: 1109917696 */
  if (f != 1109917696) return (1);
  i2 = ## f;
  if (i2 != 42) return (2);
  return (0);
}
