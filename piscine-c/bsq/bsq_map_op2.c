
#include "h_main.h"

/*
 * Reads a file, then splits it, then frees the data and returns the
 * split result.
 *
 * @param	fname	file name
 * @param	fsize	how many bytes to read
 *
 * @returns	array of strings
 */
char **bsq_read_split_free(char *fname, int fsize) {
  char *str;
  char **strs;

  str = (char *)ft_file_read(fname, fsize);
  strs = ft_strsplit(str, '\n');
  free(str);
  return (strs);
}

/*
 * Reads stdin, then splits it, then frees the data and returns the
 * split result.
 *
 * @param	fsize	how many bytes to read
 *
 * @returns	array of strings
 */
char **bsq_read_split_free_stdin(int fsize) {
  char *str;
  char **strs;

  str = (char *)ft_stdin_read(fsize);
  strs = ft_strsplit(str, '\n');
  free(str);
  return (strs);
}
