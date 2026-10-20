chmod(string, mode) {
  extrn syscall;
  return (syscall(15, string, mode));
}
