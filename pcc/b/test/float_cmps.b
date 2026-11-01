main() {
  if (!(1.5 #< 2.5)) return (1);
  if (2.5 #< 1.5) return (2);
  if (!(2.5 #> 1.5)) return (3);
  if (!(2.0 #== 2.0)) return (4);
  if (2.0 #!= 2.0) return (5);
  return (0);
}
