main() {
  if (!(5 == 5)) return (1);
  if (5 != 5) return (2);
  if (!(5 < 10)) return (3);
  if (10 < 5) return (4);
  if (!(5 <= 5)) return (5);
  if (!(5 <= 6)) return (6);
  if (!(10 > 5)) return (7);
  if (5 > 10) return (8);
  if (!(5 >= 5)) return (9);
  if (!(6 >= 5)) return (10);
  return (0);
}
