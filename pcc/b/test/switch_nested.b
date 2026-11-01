main() {
  auto x, y, res;
  x = 1;
  y = 2;
  res = 0;
  switch (x) {
    case 1:
      switch (y) {
        case 1:
          res = 10;
          break;
        case 2:
          res = 42;
          break;
        default:
          res = 99;
          break;
      }
      break;
    default:
      res = 1;
      break;
  }
  if (res != 42) return (1);
  return (0);
}
