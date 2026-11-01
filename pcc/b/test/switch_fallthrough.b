main() {
  auto a, count;
  a = 1;
  count = 0;
  switch (a) {
    case 1:
      count = count + 10;
    case 2:
      count = count + 20;
    case 3:
      count = count + 12;
      break;
    case 4:
      count = count + 100;
  }
  if (count != 42) return (1);
  return (0);
}
