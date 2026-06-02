
#include <unistd.h>

void ft_putchar(char c) { write(1, &c, 1); }

void ft_print_alphabet(void) {
  char ch;

  ch = 'a';
  while (ch <= 'z') {
    ft_putchar(ch);
    ch++;
  }
}

// int	main (void)
// {
// 	ft_print_alphabet ();
// }
