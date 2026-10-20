lchar(string, i, c) {
  auto shift, mask;
  shift = 8 * (i % 4);
  mask = ~(0377 << shift);
  string[i/4] = (string[i/4] & mask) | ((c & 0377) << shift);
}
