#include <stdio.h>
#include "libft.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }
    size_t len = ft_strlen(argv[1]);
    printf("%zu\n", len);
    return 0;
}
