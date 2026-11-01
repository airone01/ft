main() {
  auto a, b;
  a = 65280; /* 0xFF00 in decimal */
  b = 4080;  /* 0x0FF0 in decimal */
  if ((a & b) != 3840) return (1);  /* 0x0F00 */
  if ((a | b) != 65520) return (2); /* 0xFFF0 */
  if ((a ^ b) != 61680) return (3); /* 0xF0F0 */
  return (0);
}
