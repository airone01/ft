close(file) {
  extrn syscall;
  return (syscall(6, file));
}
