main() {
  auto x;
  x = 0;

  /* Since 0 is false, (x = 42) must not be evaluated */
  if (0 && (x = 42)) {
    return (1);
  }

  /* Since 1 is true, (x = 99) must not be evaluated */
  if (1 || (x = 99)) {
    return (x); // returns 0 on all is well
  }

  return (2);
}
