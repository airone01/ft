putchar(c) {
  extrn write;
  auto ch;
  ch = c;
  return (write(1, &ch, 1));
}
