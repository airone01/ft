getchar() {
  extrn read;
  auto ch;
  ch = 0;
  if (read(0, &ch, 1) <= 0)
    return (-1);
  return (ch & 0377);
}
