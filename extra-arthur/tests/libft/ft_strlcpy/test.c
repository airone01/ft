#include <stdio.h>
#include "libft.h"

int main(int argc, char **argv) {
    if (argc != 2) return 1;

    char dest[50];
    size_t size = 5;  // Test with limited buffer

    size_t result = ft_strlcpy(dest, argv[1], size);
    printf("Result: %zu\nBuffer: %s\n", result, dest);
    return 0;
}