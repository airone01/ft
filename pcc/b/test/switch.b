main() {
  auto a;
  a = 42;

  switch (a) {
    case 0:
      a = 1;
      break;
    case 41:
    case 42:
      a = 1337;
      break;
  }

  return a;
}
