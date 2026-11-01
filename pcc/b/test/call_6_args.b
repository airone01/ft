f6(a, b, c, d, e, f) {
  return (a * 100000 + b * 10000 + c * 1000 + d * 100 + e * 10 + f);
}

main() {
  if (f6(1, 2, 3, 4, 5, 6) != 123456) return (1);
  return (0);
}
