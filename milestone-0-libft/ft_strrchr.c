/* ************************************************************************** */
/*                                                                            */
/*                                                     _    ⣀⣀⣀⡀⡀⡀⡀⣀⡀⣀⣀⣀⡀  */
/*   ft_strrchr.c                                  _ _/ |   ⡇⣶⡆⡇⡾⢏⡭⡵⠀⡇⣶⡆⡇  */
/*                                                | '_| |_  ⣓⣒⠒⡃⡂⣏⡆⡯⢇⠓⠶⠖⡃  */
/*   By: elagouch <elagouch@student.42lyon.fr>    |_|_|_(@) ⢻⣊⡞⣪⢳⡗⣳⢤⣈⢍⣰⢖⡇  */
/*                                                | | |_  ) ⠜⡲⡢⣲⡯⡼⡑⡁⣝⣘⡚⢠⠅  */
/*   Created: 2024/11/11 16:25:36 by elagouch     |_  _/ /  ⡖⣒⡒⡆⠉⠧⢰⣮⣇⣂⡏⡳⡆  */
/*   Updated: 2024/11/11 16:31:43 by elagouch       |_/___| ⣇⣛⣃⡇⡿⢤⠤⠾⠡⠹⢝⣚⡁  */
/*                                                                            */
/* ************************************************************************** */

/*
 * The strrchr() function returns a pointer to the last occurrence of the char‐
 * acter c in the string s.
 *
 * @param	s	haystack
 * @param	c	needle
 *
 * @returns	pointer to the matched character or NULL if the character is not
 * found.
 */
char	*ft_strrchr(const char *s, int c)
{
	char	*se;

	se = 0;
	while (*s)
	{
		if (*s == (char)c)
			se = (char *)s;
		s++;
	}
	if (*s == (char)c)
		se = (char *)s;
	return (se);
}
