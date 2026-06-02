
#include <unistd.h>

void ft_putstr(char *str) {
  if (*str == '\0')
    return;
  write(1, str, 1);
  ft_putstr(str + sizeof(char));
}

void rec_rev_params(int argc, char **argv) {
  if (argc == 0)
    return;
  if (argc > 1)
    rec_rev_params(argc - 1, argv + 1);
  ft_putstr(*argv);
  write(1, "\n", 1);
}

int main(int argc, char **argv) { rec_rev_params(argc - 1, argv + 1); }
