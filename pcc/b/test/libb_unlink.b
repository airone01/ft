main() {
  extrn unlink;
  /* unlink non-existent file returns -ENOENT (-2) */
  if (unlink("/nonexistent_xyz_12345") != -2) return (1);
  return (0);
}
