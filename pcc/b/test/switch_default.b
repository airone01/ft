main() {
  auto a, res;
  a = 99;
  res = 0;
  switch (a) {
    case 1:
      res = 10;
      break;
    case 2:
      res = 20;
      break;
    default:
      res = 42;
      break;
  }
  if (res != 42) return (1);
  return (0);
}
