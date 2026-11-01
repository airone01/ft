exit(x) {
  extrn syscall;
  return (syscall(1, x));
}
