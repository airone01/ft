
#ifndef H_FILE_H
#define H_FILE_H

void *free_and_null_map(void *ptr, t_tile **map, t_coords coords);
void *ft_file_read(char *fname, int fsize);
void *free_and_null(void *ptr);
void *ft_stdin_read(int fsize);
void free_strs(char **strs);

#endif
