execv(string, argv, count) {
  extrn syscall;
  return (syscall(11, string, argv, 0));
}
