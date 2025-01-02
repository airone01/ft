#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int main(int argc, char **argv) {
	int	atoi_res;
	int	ft_atoi_res;

    if (argc != 2) return 1;
	atoi_res = atoi(argv[1]);
	ft_atoi_res = ft_atoi(argv[1]);
	if (atoi_res == ft_atoi_res) {
    	printf("Valid\n");
	    return 0;
	}
	printf("Result not equal to standard atoi. Original: %d Yours: %d\n", atoi_res, ft_atoi_res);
	return 0;
} // Compilation error on purpose