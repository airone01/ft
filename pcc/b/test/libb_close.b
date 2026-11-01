main() {
  extrn close;
  /* close non-existent fd 999 returns -EBADF (-9) */
  if (close(999) != -9) return (1);
  return (0);
}
