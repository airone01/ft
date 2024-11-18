/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:24:53 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/29 23:29:57 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

char	***extract_data(char *data_src, int *len)
{
    int     file;
    char    buffer[5000];
    char    **dico1;
    char    ***cube;
    int     i;

    file = open(data_src, O_RDONLY);
    read(file, buffer, 5000);
    dico1 = ft_split(buffer, "\n");
	i = 0;
    while (dico1[i++])
	{
        (*len)++;
	}
	cube = malloc(sizeof(char **) * (*len));
    i = 0;
    while (dico1[i])
    {
        cube[i] = ft_split2(dico1[i],":");
        i++;
    }
    return (cube);
}

char	***mk_cube(int *len)
{
	int		i;
	char	***cube;

	cube = malloc(41 * sizeof(char **));
	if (cube == NULL)
		return (NULL);
	i = 0;
	while (i < 41)
	{
		cube[i] = malloc(2 * sizeof(char *));
		if (cube[i] == NULL)
			return (NULL);
		i++;
	}
	cube[0][0] = ft_strdup("0");
	cube[0][1] = ft_strdup("zero");
	cube[1][0] = ft_strdup("1");
	cube[1][1] = ft_strdup("one");
	cube[2][0] = ft_strdup("2");
	cube[2][1] = ft_strdup("two");
	cube[3][0] = ft_strdup("3");
	cube[3][1] = ft_strdup("three");
	cube[4][0] = ft_strdup("4");
	cube[4][1] = ft_strdup("four");
	cube[5][0] = ft_strdup("5");
	cube[5][1] = ft_strdup("five");
	cube[6][0] = ft_strdup("6");
	cube[6][1] = ft_strdup("six");
	cube[7][0] = ft_strdup("7");
	cube[7][1] = ft_strdup("seven");
	cube[8][0] = ft_strdup("8");
	cube[8][1] = ft_strdup("eight");
	cube[9][0] = ft_strdup("9");
	cube[9][1] = ft_strdup("nine");
	cube[10][0] = ft_strdup("10");
	cube[10][1] = ft_strdup("ten");
	cube[11][0] = ft_strdup("11");
	cube[11][1] = ft_strdup("eleven");
	cube[12][0] = ft_strdup("12");
	cube[12][1] = ft_strdup("twelve");
	cube[13][0] = ft_strdup("13");
	cube[13][1] = ft_strdup("thirteen");
	cube[14][0] = ft_strdup("14");
	cube[14][1] = ft_strdup("fourteen");
	cube[15][0] = ft_strdup("15");
	cube[15][1] = ft_strdup("fifteen");
	cube[16][0] = ft_strdup("16");
	cube[16][1] = ft_strdup("sixteen");
	cube[17][0] = ft_strdup("17");
	cube[17][1] = ft_strdup("seventeen");
	cube[18][0] = ft_strdup("18");
	cube[18][1] = ft_strdup("eighteen");
	cube[19][0] = ft_strdup("19");
	cube[19][1] = ft_strdup("nineteen");
	cube[20][0] = ft_strdup("20");
	cube[20][1] = ft_strdup("twenty");
	cube[21][0] = ft_strdup("30");
	cube[21][1] = ft_strdup("thirty");
	cube[22][0] = ft_strdup("40");
	cube[22][1] = ft_strdup("forty");
	cube[23][0] = ft_strdup("50");
	cube[23][1] = ft_strdup("fifty");
	cube[24][0] = ft_strdup("60");
	cube[24][1] = ft_strdup("sixty");
	cube[25][0] = ft_strdup("70");
	cube[25][1] = ft_strdup("seventy");
	cube[26][0] = ft_strdup("80");
	cube[26][1] = ft_strdup("eighty");
	cube[27][0] = ft_strdup("90");
	cube[27][1] = ft_strdup("ninety");
	cube[28][0] = ft_strdup("100");
	cube[28][1] = ft_strdup("hundred");
	cube[29][0] = ft_strdup("1000");
	cube[29][1] = ft_strdup("thousand");
	cube[30][0] = ft_strdup("1000000");
	cube[30][1] = ft_strdup("million");
	cube[31][0] = ft_strdup("1000000000");
	cube[31][1] = ft_strdup("billion");
	cube[32][0] = ft_strdup("1000000000000");
	cube[32][1] = ft_strdup("trillion");
	cube[33][0] = ft_strdup("1000000000000000");
	cube[33][1] = ft_strdup("quadrillion");
	cube[34][0] = ft_strdup("1000000000000000000");
	cube[34][1] = ft_strdup("quintillion");
	cube[35][0] = ft_strdup("1000000000000000000000");
	cube[35][1] = ft_strdup("sextillion");
	cube[36][0] = ft_strdup("1000000000000000000000000");
	cube[36][1] = ft_strdup("septillion");
	cube[37][0] = ft_strdup("1000000000000000000000000000");
	cube[37][1] = ft_strdup("octillion");
	cube[38][0] = ft_strdup("1000000000000000000000000000000");
	cube[38][1] = ft_strdup("nonillion");
	cube[39][0] = ft_strdup("1000000000000000000000000000000000");
	cube[39][1] = ft_strdup("decillion");
	cube[40][0] = ft_strdup("1000000000000000000000000000000000000");
	cube[40][1] = ft_strdup("undecillion");
	*len = 41;
	return (cube);
}

void	del_cube(char ***cube, int len)
{
	int		i;
	int		j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < 2)
		{
			free(cube[i][j]);
			j++;
		}
		free(cube[i]);
		i++;
	}
	free(cube);
}

int	calc_qty(char *nbr)
{
	int	len;

	len = (ft_strlen(nbr) - 1) / 3;
	return  (len);
}

int	main(int argc, char **argv)
{
	int		len;
	char	***cube;
	struct	s_lang_args args;

	len = 0;
	if (argc > 2)
	{
		cube = extract_data(argv[1], &len);
		args.nbr = argv[2];
	}
	else
	{
		cube = mk_cube(&len);
		args.nbr = argv[1];
	}
	args.cube = cube;
	args.len = len;
	args.ite = 0;
	args.qty = calc_qty(args.nbr);
	putnbr_lang(args);
	return (0);
}
