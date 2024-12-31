#include <stdio.h>
#include <string.h>
#include "libft.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }
    char buffer[1024];
    ft_strcpy(buffer, argv[1]);
    printf("%s\n", buffer);
    // Also check null termination
    printf("Length: %zu\n", strlen(buffer));
    return 0;
}