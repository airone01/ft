main() {
  extrn creat, write, open, read, close, unlink, char, buf;
  auto fd, n;

  fd = creat("/tmp/b_test_read.tmp", 0644);
  if (fd < 0) return (1);
  write(fd, "XYZ123", 6);
  close(fd);

  fd = open("/tmp/b_test_read.tmp", 0);
  if (fd < 0) return (2);

  buf[0] = buf[1] = 0;
  n = read(fd, buf, 6);
  close(fd);
  unlink("/tmp/b_test_read.tmp");

  if (n != 6) return (3);
  if (char(buf, 0) != 'X') return (4);
  if (char(buf, 1) != 'Y') return (5);
  if (char(buf, 2) != 'Z') return (6);
  if (char(buf, 3) != '1') return (7);
  if (char(buf, 4) != '2') return (8);
  if (char(buf, 5) != '3') return (9);

  return (0);
}
buf[8];
