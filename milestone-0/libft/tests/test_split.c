#include "test.h"

static void free_split(char **tab) {
  if (!tab)
    return;
  for (size_t i = 0; tab[i]; i++) {
    free(tab[i]);
  }
  free(tab);
}

int main(void) {
  // Simple split
  char **tab = ft_split("hello world 42", ' ');
  assert(tab != NULL);
  assert(strcmp(tab[0], "hello") == 0);
  assert(strcmp(tab[1], "world") == 0);
  assert(strcmp(tab[2], "42") == 0);
  assert(tab[3] == NULL);
  free_split(tab);

  // Consecutive, leading, and trailing delimiters
  tab = ft_split("---apple---banana--cherry-", '-');
  assert(tab != NULL);
  assert(strcmp(tab[0], "apple") == 0);
  assert(strcmp(tab[1], "banana") == 0);
  assert(strcmp(tab[2], "cherry") == 0);
  assert(tab[3] == NULL);
  free_split(tab);

  // No delimiter in string
  tab = ft_split("single_word", ' ');
  assert(tab != NULL);
  assert(strcmp(tab[0], "single_word") == 0);
  assert(tab[1] == NULL);
  free_split(tab);

  // Only delimiters
  tab = ft_split("     ", ' ');
  assert(tab != NULL);
  assert(tab[0] == NULL);
  free_split(tab);

  // Empty string
  tab = ft_split("", ' ');
  assert(tab != NULL);
  assert(tab[0] == NULL);
  free_split(tab);

  return 0;
}
