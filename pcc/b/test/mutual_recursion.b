is_even(n) {
  extrn is_odd;
  if (n == 0) return (1);
  return (is_odd(n - 1));
}

is_odd(n) {
  extrn is_even;
  if (n == 0) return (0);
  return (is_even(n - 1));
}

main() {
  if (is_even(10) != 1) return (1);
  if (is_even(7) != 0) return (2);
  if (is_odd(7) != 1) return (3);
  if (is_odd(10) != 0) return (4);
  return (0);
}
