
// #include <stdio.h>

void ft_swap(int *a, int *b) {
  int val_a;
  int val_b;

  val_a = *a;
  val_b = *b;
  *a = val_b;
  *b = val_a;
}

// int	main(void)
// {
// 	int a;
// 	int b;
//
// 	a = 69;
// 	b = 420;
// 	printf("a: %d, b: %d\n", a, b);
//
// 	ft_swap (&a, &b);
// 	printf("a: %d, b: %d", a, b);
// }
