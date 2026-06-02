
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void) {
  size_t fd;
  char *line;

  fd = open("./1char.txt", O_RDONLY);
  while (1) {
    line = get_next_line(fd);
    if (!line)
      return (0);
    printf("Line >%s", line);
    free(line);
  }
}

int main(void) {
  int fd;
  char *line;
  char *files[] = {"./1char.txt",           "./variable_nls.txt",
                   "./lines_around_10.txt", "./read_error.txt",
                   "./only_nl.txt",         "./one_line_no_nl.txt",
                   "./multiple_nl.txt",     "./giant_line.txt",
                   "./empty.txt",           NULL};

  for (int i = 0; files[i]; i++) {
    printf("\nTesting %s:\n", files[i]);
    fd = open(files[i], O_RDONLY);
    if (fd < 0) {
      printf("Failed to open %s\n", files[i]);
      continue;
    }
    while ((line = get_next_line(fd))) {
      printf("Line: %s\n", line);
      free(line);
    }
    close(fd);
  }
  // Test invalid fd
  printf("\nTesting invalid fd:\n");
  line = get_next_line(-1);
  printf("Invalid fd result: %s\n", line ? line : "NULL");
  free(line);
  return (0);
}
