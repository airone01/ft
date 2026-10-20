open(string, mode) {
  extrn syscall;
  return (syscall(5, string, mode));
}
