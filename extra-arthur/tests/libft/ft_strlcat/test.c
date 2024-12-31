#include <stdio.h>
#include <string.h>
#include "libft.h"

int main(int argc, char **argv) {
    if (argc != 2) return 1;

    char dest[50];
    size_t size = 10;  // Test with limited buffer

    // Initialize dest with 'x' characters
    memset(dest, 'x', sizeof(dest));
    dest[0] = 'h';
    dest[1] = 'i';
    dest[2] = '\0';

    size_t result = ft_strlcat(dest, argv[1], size);
    printf("Result: %zu\nBuffer: %s\n", result, dest);
    return 0;
}