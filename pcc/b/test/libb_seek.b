main() {
  extrn creat, write, open, seek, read, close, unlink, char, buf;
  auto fd, n, pos;

  fd = creat("/tmp/b_test_seek.tmp", 0644);
  write(fd, "ABCDEFGH", 8);
  close(fd);

  fd = open("/tmp/b_test_seek.tmp", 0);
  pos = seek(fd, 4, 0);
  if (pos != 4) return (1);

  buf[0] = 0;
  n = read(fd, buf, 4);
  close(fd);
  unlink("/tmp/b_test_seek.tmp");

  if (n != 4) return (2);
  if (char(buf, 0) != 'E') return (3);
  if (char(buf, 1) != 'F') return (4);
  if (char(buf, 2) != 'G') return (5);
  if (char(buf, 3) != 'H') return (6);

  return (0);
}
buf[4];
