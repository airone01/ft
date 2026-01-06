/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:58:23 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/02 23:27:19 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stock_str.h"
#include <stdint.h>
#include <stdlib.h>

/**
 * The  memset() function fills the first n bytes of the memory area pointed to
 * by s with the constant byte c.
 * @param	s	Pointer
 * @param	c	Constant byte
 * @param	n	Size in number of bytes
 * @returns     Pointer to the memory area s
 */
void	*ft_memset(void *s, int c, size_t n)
{
	uint8_t	*pt;

	if (n != 0)
	{
		pt = s;
		while (n != 0)
		{
			*pt++ = (uint8_t)c;
			n--;
		}
	}
	return (s);
}

/**
 * The  bzero()  function erases the data in the n bytes of the memory starting
 * at the location pointed to by s, by writing zeros (bytes containing '\0') to
 * that area.
 * @param	s	Pointer
 * @param	n	Size in number of bytes
 * @returns	pointer to the memory area s
 */
void	*ft_bzero(void *s, size_t n)
{
	return (ft_memset(s, 0, n));
}

/**
 * The calloc() function allocates memory for an array  of  nmemb  elements  of
 * size  bytes  each and returns a pointer to the allocated memory.  The memory
 * is set to zero.  If nmemb or size is 0, then calloc() returns  either  NULL,
 * or  a  unique pointer value that can later be successfully passed to free().
 * If the multiplication of nmemb and size would result  in  integer  overflow,
 * then  calloc() returns an error.  By contrast, an integer overflow would not
 * be detected in the following call to malloc(), with the result that  an  in‐
 * correctly sized block of memory would be allocated:
 * ```c
 * malloc(nmemb * size);
 * ```
 * @param	nmemb	Length of the variable
 * @param	size	Length of the type of the variable
 * @returns	pointer Filled with NUL
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size && nmemb > SIZE_MAX / size)
		return (0);
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (0);
	return (ft_bzero(ptr, size * nmemb));
}

/**
 * Gets the length of a string.
 * @param	str	String to get length from
 * @retuns      Length of str
 */
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/**
 * Duplicates a string.
 * @param	s	String to duplicate
 * @returns     String if everything worked
 * @returns     NULL if malloc failed
 */
char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dst;

	dst = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!dst)
		return (0);
	i = 0;
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	return ((char *)dst);
}

struct s_stock_str	*ft_strs_to_tab(int ac, char **av)
{
	int			i;
	t_stock_str	*stk;

	if ((stk = ft_calloc(ac + 1, sizeof(t_stock_str))) == ((void *)0))
		return ((void *)0);
	i = 0;
	while (i < ac)
	{
		stk[i].size = ft_strlen(av[i]);
		stk[i].str = av[i];
		stk[i].copy = ft_strdup(av[i]);
		i++;
	}
	stk[i].str = 0;
	return (stk);
}
