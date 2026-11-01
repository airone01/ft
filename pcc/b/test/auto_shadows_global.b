extrn gvar;

shadow_func() {
  auto gvar;
  gvar = 42;
  return (gvar);
}

main() {
  gvar = 999;
  if (shadow_func() != 42) return (1);
  if (gvar != 999) return (2);
  return (0);
}

gvar 999;
