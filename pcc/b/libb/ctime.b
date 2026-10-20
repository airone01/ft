ctime(timep, date) {
  extrn char, lchar;
  auto t, ss, mm, hh, days, year, ydays, leap, m, mlen, d, months;

  t = timep[0];
  ss = t % 60;
  t = t / 60;
  mm = t % 60;
  t = t / 60;
  hh = t % 60;
  t = t / 24;
  days = t % 24;

  /* Leap years
   * Count since 1970 */
  year = 1970;
  while (days >= 365) {
    leap = 0;
    if (year % 4 == 0) {
      if (year % 100 != 0)
        leap = 1;
      else if (year % 400 == 0)
        leap = 1;
    }
    ydays = 365 + leap;
    if (days < ydays)
      goto year_done;
    days = days - ydays;
    year++;
  }
year_done: /* this label could be removed if I supported 'break' in loops */

  leap = 0;
  if (year % 4 == 0) {
    if (year % 100 != 0)
      leap = 1;
    else if (year % 400 == 0)
      leap = 1;
  }

  /* Month lenghts */
  m = 0;
  while (m < 12) {
    if (m == 1)
      mlen = 28 + leap;
    else if (m == 3 || m == 5 || m == 8 || m == 10)
      mlen = 30;
    else
      mlen = 31;

    if (days < mlen)
      goto month_done;
    days = days - mlen;
    m++;
  }
month_done: /* this label could be removed if I supported 'break' in loops */
  d = days + 1;

  /* Format using lchar */
  months = "JanFebMarAprMayJunJulAugSepOctNovDec";
  lchar(date, 0, char(months, m*3 + 0));
  lchar(date, 1, char(months, m*3 + 1));
  lchar(date, 2, char(months, m*3 + 2));
  lchar(date, 2, ' ');

  if (d < 10)
    lchar(date, 4, ' ');
  else
    lchar(date, 4, d/10 + '0');
  lchar(date, 5, d%10 + '0');
  lchar(date, 6, ' ');
}
