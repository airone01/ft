main() {
  auto side_effect;
  side_effect = 0;
  if (1 || (side_effect = 1)) {
    if (side_effect != 0) return (1);
  } else {
    return (2);
  }
  if (0 || (side_effect = 1)) {
    if (side_effect != 1) return (3);
  } else {
    return (4);
  }
  return (0);
}
