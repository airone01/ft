extrn g_neg, g_vec;

main() {
  if (g_neg != -42) return (1);
  if (g_vec[0] != -10) return (2);
  if (g_vec[1] != -20) return (3);
  if (g_vec[2] != 30) return (4);
  return (0);
}

g_neg -42;
g_vec[3] -10, -20, 30;
