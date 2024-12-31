#include <stdio.h>
#include "libft.h"

int main(int argc, char **argv) {
    if (argc != 2 || !argv[1][0]) return 1;
    printf("%d\n", ft_isalpha(argv[1][0]));
    return 0;
}