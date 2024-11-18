/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:21:04 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/23 10:34:24 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	if (*str == '\0')
		return (0);
	return (1 + ft_strlen(str + 1));
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	else
		return (s1[i] - s2[i]);
}

void	rec_params(int argc, char **argv)
{
	ft_putstr(*argv);
	write(1, "\n", 1);
	if (argc == 0)
		return ;
	if (argc > 1)
		rec_params(argc - 1, argv + 1);
}

int	main(int argc, char **argv)
{
	int		i;
	int		swapped;
	char	*temp;

	swapped = 1;
	while (swapped)
	{
		i = 0;
		swapped = 0;
		while (++i < argc - 1)
		{
			if (ft_strcmp(argv[i], argv[i + 1]) > 0)
			{
				temp = argv[i];
				argv[i] = argv[i + 1];
				argv[i + 1] = temp;
				swapped = 1;
			}
		}
	}
	rec_params(argc, argv);
}
