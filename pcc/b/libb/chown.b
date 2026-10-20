chown(string, owner) {
  extrn syscall;
  return (syscall(212, string, owner, -1));
}
