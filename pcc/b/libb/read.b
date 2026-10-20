read(file, buffer, count) {
  extrn syscall;
  return (syscall(3, file, buffer, count));
}
