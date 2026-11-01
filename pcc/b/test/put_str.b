write(file, buffer, count) {
  extrn syscall;
  return (syscall(4, file, buffer, count));
}

putchar(c) {
  extrn write;
  auto ch;
  ch = c;
  return (write(1, &ch, 1));
}

char(string, i) {
  return ((string[i/4] >> (8 * (i % 4))) & 0377);
}

main() {
  extrn putchar, char;
  auto i, s;
  i = 0;
  s = "hello, world\n";
  while (char(s, i)) {
    putchar(char(s, i));
    i++;
  }
}

