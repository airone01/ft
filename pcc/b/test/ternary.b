extrn side_effect_count;

side_effect() {
  side_effect_count++;
  return (999);
}

main() {
  auto a, b, res;

  /* Basic true/false */
  res = 1 ? 42 : 100;
  if (res != 42) return (1);

  res = 0 ? 42 : 100;
  if (res != 100) return (2);

  /* Expression condition */
  a = 10;
  b = 20;
  res = (a < b) ? (b - a) : (a - b);
  if (res != 10) return (3);

  res = (a > b) ? (b - a) : (a - b);
  if (res != -10) return (4);

  /* Nested right-associative: a ? b : c ? d : e */
  res = 0 ? 1 : 1 ? 2 : 3;
  if (res != 2) return (5);

  res = 0 ? 1 : 0 ? 2 : 3;
  if (res != 3) return (6);

  /* Short circuit when true: false branch must NOT be executed */
  side_effect_count = 0;
  res = 1 ? 77 : side_effect();
  if (res != 77) return (7);
  if (side_effect_count != 0) return (8);

  /* Short circuit when false: true branch must NOT be executed */
  side_effect_count = 0;
  res = 0 ? side_effect() : 88;
  if (res != 88) return (9);
  if (side_effect_count != 0) return (10);

  return (0);
}

side_effect_count 0;
