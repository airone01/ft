link(string1, string2) {
  extrn syscall;
  return (syscall(9, string1, string2));
}
