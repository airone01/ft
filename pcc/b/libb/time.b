time(timev) {
  extrn syscall;
  return (syscall(13, timev));
}
