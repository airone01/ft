extrn gval;

get_val(gval) {
  return (gval);
}

main() {
  gval = 100;
  if (get_val(42) != 42) return (1);
  if (gval != 100) return (2);
  return (0);
}

gval 100;
