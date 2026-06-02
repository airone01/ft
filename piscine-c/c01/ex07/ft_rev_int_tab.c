
void ft_swap(int *p, int *p1) {
  int tmp;

  tmp = *p;
  *p = *p1;
  *p1 = tmp;
}

void ft_rev_int_tab(int *tab, int size) {
  int swaps;
  int i;

  i = 0;
  swaps = size / 2;
  // size/2 is the "tricky" thing to grasp here
  while (swaps--)
    ft_swap(&(*(tab + i++)), &(tab[--size]));
}
