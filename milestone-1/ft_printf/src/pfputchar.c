
#include <unistd.h>

ssize_t pfputchar(int fd, char c) { return (write(fd, &c, 1)); }
