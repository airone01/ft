chdir(string) {
  extrn syscall;
  return (syscall(12, string));
}
