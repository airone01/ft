main() {
  extrn creat, close, chmod, unlink;
  auto fd, ret;

  fd = creat("/tmp/b_test_chmod.tmp", 0600);
  close(fd);

  ret = chmod("/tmp/b_test_chmod.tmp", 0644);
  unlink("/tmp/b_test_chmod.tmp");

  if (ret != 0) return (1);
  return (0);
}
