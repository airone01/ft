main() {
  extrn char, lchar, buf;
  buf[0] = 0;
  buf[1] = 0;

  lchar(buf, 0, 'H');
  lchar(buf, 1, 'E');
  lchar(buf, 2, 'L');
  lchar(buf, 3, 'L');
  lchar(buf, 4, 'O');

  if (char(buf, 0) != 'H') return (1);
  if (char(buf, 1) != 'E') return (2);
  if (char(buf, 2) != 'L') return (3);
  if (char(buf, 3) != 'L') return (4);
  if (char(buf, 4) != 'O') return (5);
  return (0);
}
buf[4];
