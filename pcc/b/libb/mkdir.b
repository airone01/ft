mkdir(string, mode) {
  extrn syscall;
  return (syscall(39, string, mode));
}
