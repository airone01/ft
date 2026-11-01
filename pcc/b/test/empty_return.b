set_val(ptr, val) {
  ptr[0] = val;
  return;
}

main() {
  auto x;
  x = 0;
  set_val(&x, 42);
  if (x != 42) return (1);
  return (0);
}
