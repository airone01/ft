creat(string, mode) {
  extrn syscall;
  return (syscall(8, string, mode));
}
