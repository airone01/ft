setuid(id) {
  extrn syscall;
  return (syscall(213, id));
}
