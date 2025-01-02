#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int main(int argc, char **argv) {
    if (argc != 2) return 1;
	if (ft_atoi(argv[1]) == atoi(argv[1])) {
    	printf("y\n");
	    return 0;
	}
	printf("n\n");
	return 0;
}