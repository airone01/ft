wait() {
  extrn syscall;
  return (syscall(7, -1, 0, 0));
}
