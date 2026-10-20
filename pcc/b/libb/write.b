write(file, buffer, count) {
  extrn syscall;
  return (syscall(4, file, buffer, count));
}
