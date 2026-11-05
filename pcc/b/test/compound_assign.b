extrn vec;

main() {
  auto x, y, r;

  /* Addition */
  x = 10;
  x =+ 5;
  if (x != 15) return (1);
  x += 5;
  if (x != 20) return (2);

  /* Subtraction */
  x =- 6;
  if (x != 14) return (3);
  x -= 4;
  if (x != 10) return (4);

  /* Multiplication */
  x =* 3;
  if (x != 30) return (5);
  x *= 2;
  if (x != 60) return (6);

  /* Division */
  x =/ 4;
  if (x != 15) return (7);
  x /= 3;
  if (x != 5) return (8);

  /* Modulo */
  x = 23;
  x =% 10;
  if (x != 3) return (9);
  x = 29;
  x %= 7;
  if (x != 1) return (10);

  /* Bitwise shifts */
  x = 3;
  x =<< 2;
  if (x != 12) return (11);
  x <<= 1;
  if (x != 24) return (12);
  x =>> 2;
  if (x != 6) return (13);
  x >>= 1;
  if (x != 3) return (14);

  /* Bitwise AND, OR, XOR */
  x = 15;
  x =& 6;
  if (x != 6) return (15);
  x &= 4;
  if (x != 4) return (16);
  x =| 1;
  if (x != 5) return (17);
  x |= 10;
  if (x != 15) return (18);
  x =^ 9;
  if (x != 6) return (19);
  x ^= 6;
  if (x != 0) return (20);

  /* Comparison assignments */
  x = 10;
  x === 10;
  if (x != 1) return (21);
  x = 10;
  x === 20;
  if (x != 0) return (22);

  x = 10;
  x =!= 20;
  if (x != 1) return (23);
  x = 10;
  x =!= 10;
  if (x != 0) return (24);

  x = 5;
  x =< 10;
  if (x != 1) return (25);
  x = 15;
  x =< 10;
  if (x != 0) return (26);

  x = 10;
  x =<= 10;
  if (x != 1) return (27);
  x = 11;
  x =<= 10;
  if (x != 0) return (28);

  x = 15;
  x => 10;
  if (x != 1) return (29);
  x = 5;
  x => 10;
  if (x != 0) return (30);

  x = 10;
  x =>= 10;
  if (x != 1) return (31);
  x = 9;
  x =>= 10;
  if (x != 0) return (32);

  /* Assignment as rvalue */
  x = 20;
  r = (x =+ 7);
  if (r != 27) return (33);
  if (x != 27) return (34);

  /* Array compound assignment */
  vec[0] = 50;
  vec[1] = 100;
  vec[0] =+ 25;
  if (vec[0] != 75) return (35);
  vec[0] -= 15;
  if (vec[0] != 60) return (36);
  vec[0] =* 2;
  if (vec[0] != 120) return (37);
  vec[0] /= 4;
  if (vec[0] != 30) return (38);
  vec[0] =% 7;
  if (vec[0] != 2) return (39);
  vec[0] =<< 3;
  if (vec[0] != 16) return (40);
  vec[0] =>> 2;
  if (vec[0] != 4) return (41);
  vec[0] =& 6;
  if (vec[0] != 4) return (42);
  vec[0] =| 3;
  if (vec[0] != 7) return (43);
  vec[0] =^ 5;
  if (vec[0] != 2) return (44);
  vec[0] === 2;
  if (vec[0] != 1) return (45);

  return (0);
}

vec[5];
