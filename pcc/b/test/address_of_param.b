addrof_arg(x) {
  auto p;
  p = &x;
  *p = 100;
  return (x);
}

main() {
  if (addrof_arg(42) != 100) return (1);
  return (0);
}
