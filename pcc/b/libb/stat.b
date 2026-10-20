stat(string, status) {
  extrn syscall;
  return (syscall(106, string, status));
}
