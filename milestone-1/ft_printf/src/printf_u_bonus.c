#include "ft_printf_bonus.h"

static int get_unumlen(unsigned int nbr) {
  int len;

  len = 0;
  if (nbr == 0)
    return (1);
  while (nbr > 0) {
    len++;
    nbr /= 10;
  }
  return (len);
}

static void calc_upad(t_format *fmt, unsigned int nbr, int *pad) {
  pad[2] = get_unumlen(nbr);
  if (nbr == 0 && fmt->precision == 0)
    pad[2] = 0;
  pad[0] = 0;
  if (fmt->precision > pad[2])
    pad[0] = fmt->precision - pad[2];
  else if (fmt->zero && fmt->precision == -1 && !fmt->minus)
    pad[0] = fmt->width - pad[2];
  if (pad[0] < 0)
    pad[0] = 0;
  pad[1] = fmt->width - (pad[2] + pad[0]);
  if (pad[1] < 0)
    pad[1] = 0;
}

long print_unsigned(int fd, t_format *fmt, unsigned int nbr) {
  long count;
  int pad[3];

  count = 0;
  calc_upad(fmt, nbr, pad);
  if (!fmt->minus)
    count += print_padding(fd, 0, pad[1], ' ');
  count += print_padding(fd, 0, pad[0], '0');
  if (pad[2] > 0)
    count += pfputnbru_base(fd, nbr, BASE_10);
  if (fmt->minus)
    count += print_padding(fd, 0, pad[1], ' ');
  return (count);
}
