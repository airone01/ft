exit() {
  extrn syscall;
  return (syscall(1, 0));
}
