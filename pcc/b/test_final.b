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

