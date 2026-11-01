main() {
  extrn mkdir, chdir, syscall;
  auto ret;

  ret = mkdir("/tmp/b_test_dir_check", 0755);
  if (ret != 0) return (1);

  ret = chdir("/tmp/b_test_dir_check");
  if (ret != 0) return (2);

  chdir("/tmp");
  syscall(40, "/tmp/b_test_dir_check");

  return (0);
}
