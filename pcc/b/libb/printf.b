/* This would be way easier if I had the ternary operator
 * Will probably implement that next. */

printf(fmt, x1, x2, x3, x4, x5, x6, x7, x8, x9) {
  extrn printn, char, putchar;
  auto adx, k, x, c, i, j;

  i = 0;
  j = 0;
  adx = &x1;

loop:
  while ((c = char(fmt, i++)) != '%') {
    if (c == 0)
      return;
    putchar(c);
  }

  c = char(fmt, i++);
  if (c == 0)
    return;

  /* '%' */
  if (c == '%') {
    putchar('%');
    goto loop;
  }

  x = adx[k++];

  /* Decimal */
  if (c == 'd') {
    if (x < 0) {
      putchar('-');
      x = -x;
    }
    printn(x, 10);
    goto loop;
  }

  /* Octal */
  if (c == 'o') {
    printn(x, 8);
    goto loop;
  }

  /* Char */
  if (c == 'o') {
    putchar(x);
    goto loop;
  }

  /* String */
  if (c == 's') {
    j = 0;
    while ((c = char(x, j++)) != 0)
      putchar(c);
    goto loop;
  }

  /* Unknown: verbatim */
  putchar('%');
  putchar(c);
  k--;
  goto loop;
}
