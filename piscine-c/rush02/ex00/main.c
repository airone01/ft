#include "h_putnbr_lang.h"
#include "h_rush.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char ***extract_data(char *data_src, int *len) {
  int file;
  char buffer[5000];
  char **dico1;
  char ***cube;
  int i;

  file = open(data_src, O_RDONLY);
  (void)!read(file, buffer, 5000);
  dico1 = ft_split_charset(buffer, "\n");
  i = 0;
  while (dico1[i++]) {
    (*len)++;
  }
  cube = malloc(sizeof(char **) * (*len));
  i = 0;
  while (dico1[i]) {
    cube[i] = ft_split_charset2(dico1[i], ":");
    i++;
  }
  return (cube);
}

void del_cube(char ***cube, int len) {
  int i;
  int j;

  i = 0;
  while (i < len) {
    j = 0;
    while (j < 2) {
      free(cube[i][j]);
      j++;
    }
    free(cube[i]);
    i++;
  }
  free(cube);
}

int calc_qty(char *nbr) {
  int len;

  len = (ft_strlen(nbr) - 1) / 3;
  return (len);
}

int main(int argc, char **argv) {
  int len;
  char ***cube;
  struct s_lang_args args;

  len = 0;
  if (argc > 2) {
    cube = extract_data(argv[1], &len);
    args.nbr = argv[2];
  } else {
    cube = mk_cube(&len);
    args.nbr = argv[1];
  }
  args.cube = cube;
  args.len = len;
  args.ite = 0;
  args.qty = calc_qty(args.nbr);
  putnbr_lang(args);
  return (0);
}
