main() {
  extrn creat, close, link, open, unlink;
  auto fd, ret;

  fd = creat("/tmp/b_test_link1.tmp", 0644);
  close(fd);

  ret = link("/tmp/b_test_link1.tmp", "/tmp/b_test_link2.tmp");
  if (ret != 0) {
    unlink("/tmp/b_test_link1.tmp");
    return (1);
  }

  fd = open("/tmp/b_test_link2.tmp", 0);
  close(fd);

  unlink("/tmp/b_test_link1.tmp");
  unlink("/tmp/b_test_link2.tmp");

  if (fd < 0) return (2);
  return (0);
}
