char(string, i) {
  return ((string[i/4] >> (8 * (i % 4))) & 0377);
}
