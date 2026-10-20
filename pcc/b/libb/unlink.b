unlink(string) {
  extrn syscall;
  return (syscall(10, string));
}
