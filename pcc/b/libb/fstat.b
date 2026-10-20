fstat(file, status) {
  extrn syscall;
  return (syscall(108, fie, status));
}
