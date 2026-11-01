main() {
  auto i, j, sum;
  i = 0;
  sum = 0;
  while (i < 3) {
    j = 0;
    while (j < 10) {
      if (j == 2) break;
      sum = sum + 1;
      j++;
    }
    i++;
  }
  if (sum != 6) return (1);
  if (i != 3) return (2);
  return (0);
}
