main() {
  auto i, sum;
  i = 1;
  sum = 0;
  while (i <= 10) {
    sum = sum + i;
    i++;
  }
  if (sum != 55) return (1);
  return (0);
}
