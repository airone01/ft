#include <stdio.h>
#include <string.h>
#include "libft.h"

int main(int argc, char **argv) {
    if (argc != 2) return 1;

    char str[] = "Hello World";
    void *result = ft_memchr(str, argv[1][0], strlen(str));
    if (result)
        printf("Found at position: %ld\n", (char*)result - str);
    else
        printf("Not found\n");
    return 0;
}