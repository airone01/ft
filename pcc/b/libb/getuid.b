getuid() {
  extrn syscall;
  return (syscall(199));
}
