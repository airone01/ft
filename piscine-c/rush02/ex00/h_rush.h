
#ifndef H_RUSH_H
#define H_RUSH_H

// Rush-specific
char ***mk_cube(int *len);
char *find_word(char ***cube, int len, int u, int qty);
struct s_lang_args {
  char ***cube;
  char *nbr;
  int len;
  int ite;
  int qty;
};

#endif
