/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:00:50 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/25 20:07:27 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h> // yes
//
// int	ft_strlen(char *str)
// {
// 	if (*str == '\0')
// 		return (0);
// 	return (ft_strlen(str + sizeof(char)) + 1);
// }
//
// char	*ft_strcpy(char *dest, char *src)
// {
// 	int		i;
//
// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	return (dest);
// }
//
// char	*ft_strstr_custom(char *str, char *to_find, int *path)
// {
// 	int	i;
// 	int	j;
//
// 	if (*to_find == '\0')
// 		return (str);
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == to_find[0])
// 		{
// 			j = 0;
// 			while (str[i + j] == to_find[j] && to_find[j] != '\0')
// 				j++;
// 			if (to_find[j] == '\0')
// 			{
// 				*path = i;
// 				return (str + i);
// 			}
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }
//
// char	*ft_until(char *str, int path)
// {
// 	int		i;
// 	char	*dest;
//
// 	dest = malloc(ft_strlen(str));
// 	i = 0;
// 	while (i++ < path)
// 		dest[i] = str[i];
// 	dest[i + 1] = '\0';
// 	return (dest);
// }
//
// char	**ft_split(char *str, char *charset)
// {
// 	int		cs_len;
// 	int		path;
// 	int		i;
// 	char	*right;
// 	char	*tmp;
// 	char	**res;
//
// 	cs_len = ft_strlen(charset);
// 	tmp = malloc(sizeof(char) * ft_strlen(str));
// 	res = malloc(sizeof(char **));
// 	ft_strcpy(tmp, str);
// 	i = 0;
// 	right = "";
// 	while (right != NULL)
// 	{
// 		path = 0;
// 		right = ft_strstr_custom(str, charset, &path);
// 		res[i] = malloc((path + 1) * sizeof(char));
// 		ft_strcpy(res[i], tmp);
// 		tmp += path;
// 		i++;
// 	}
// 	return (res);
// }
//
// int	main(void)
// {
// 	char	*haystack = "Somebody once told me the world is gonna roll me.";
// 	char	**hagrah;
// 	int	i;
//
// 	hagrah = ft_split(haystack, " m");
// 	i = 0;
// 	while (hagrah[i] != 0)
// 	{
// 		printf("%s\n", hagrah[i++]);
// 		i++;
// 	}
// }
