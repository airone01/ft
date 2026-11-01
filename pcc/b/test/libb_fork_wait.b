main() {
  extrn fork, wait, exit;
  auto pid, wpid;
  pid = fork();
  if (pid == 0) {
    exit(0);
  }
  wpid = wait();
  if (wpid == pid) return (0);
  return (1);
}
