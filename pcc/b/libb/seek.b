seek(file, offset, pointer) {
  extrn syscall;
  return (syscall(19, file, offset, pointer));
}
