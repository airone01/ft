main() {
  extrn creat, write, close, unlink;
  auto fd, ret;
  fd = creat("/tmp/b_test_file_cycle.tmp", 0644);
  if (fd < 0) return (1);

  ret = write(fd, "test
", 5);
  if (ret != 5) return (2);

  ret = close(fd);
  if (ret != 0) return (3);

  ret = unlink("/tmp/b_test_file_cycle.tmp");
  if (ret != 0) return (4);

  return (0);
}
