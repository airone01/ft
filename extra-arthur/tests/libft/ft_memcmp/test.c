#include <stdio.h>
#include "libft.h"

int main(int argc, char **argv) {
    if (argc != 2) return 1;

    char s1[] = "Hello";
    printf("%d\n", ft_memcmp(s1, argv[1], 5));
    return 0;
}