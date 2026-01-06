/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:32:24 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/23 13:54:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <errno.h>   // errno
# include <limits.h>  // LLONG_MAX
# include <stdbool.h> // bool
# include <stdint.h>  // SIZE_MAX
# include <stdlib.h>  // malloc, free
# include <unistd.h>  // write

// Bonuses
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

# define DBL_EPSILON 2.2204460492503131e-16 // <float.h> is forbidden by norm

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Bonuses ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Bored to doxygen those
void				ft_lstadd_back(t_list **lst, t_list *new_list);
void				ft_lstadd_front(t_list **lst, t_list *new_list);
t_list				*ft_lstat(t_list *lst, unsigned long index);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
unsigned long		ft_lstsize(t_list *lst);

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// Memory ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Erases data by writing zeros to a memory area.
 *
 * @param s Pointer to the memory area to be zeroed.
 * @param n Number of bytes to write zeros to.
 * @return void* Pointer s
 */
void				*ft_bzero(void *s, size_t n);

/**
 * @brief Allocates zero-initialized memory for an array.
 *
 * This function allocates memory for an array of @p nmemb elements, each of
 * @p size bytes, and initializes all bytes in the allocated memory to zero.
 *
 * @param nmemb Number of elements.
 * @param size Size of each element in bytes.
 * @return void* A pointer to the allocated zero-initialized memory, or NULL if
 *               the allocation fails or an overflow occurs.
 */
void				*ft_calloc(unsigned long nmemb, size_t size);

/**
 * @brief Locates the first occurrence of a byte in a memory area.
 *
 * @param s Memory area to scan.
 * @param c Byte to search for (interpreted as uint8_t).
 * @param n Maximum number of bytes to scan.
 * @return void* Pointer to the matching byte, or NULL if not found.
 */
void				*ft_memchr(const void *s, uint8_t c, size_t n);

/**
 * @brief Compares two memory areas.
 *
 * @param s1 First memory area.
 * @param s2 Second memory area.
 * @param n Maximum number of bytes to compare.
 * @return int Less than 0 if s1 < s2, 0 if s1 = s2, greater than 0 if s1 > s2.
 *
 * @note If n is zero, the return value is zero.
 */
int					ft_memcmp(const void *s1, const void *s2, unsigned long n);

/**
 * @brief Copies bytes from one memory area to another (non-overlapping).
 *
 * @param dest Destination memory area.
 * @param src Source memory area.
 * @param n Number of bytes to copy.
 * @return void* Pointer to the destination memory area.
 *
 * @warning Memory areas must not overlap. Use ft_memmove for overlapping areas.
 */
void				*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Copies bytes from one memory area to another (safely handles
 *        overlapping).
 *
 * @param dest Destination memory area.
 * @param src Source memory area.
 * @param n Number of bytes to copy.
 * @return void* Pointer to the destination memory area.
 */
void				*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Fills a memory area with a constant byte.
 *
 * @param s Memory area to fill.
 * @param c Byte value to set (interpreted as uint8_t).
 * @param n Number of bytes to fill.
 * @return void* Pointer to the memory area.
 */
void				*ft_memset(void *s, uint8_t c, size_t n);

/**
 * @brief Reallocates a memory block.
 *
 * @param ptr The pointer to the memory block to reallocate.
 * @param old_size The old size of the memory block.
 * @param new_size The new size of the memory block.
 * @return void* The reallocated memory block, or NULL if allocation fails.
 */
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);

/**
 * @brief Reallocates a memory block and initializes new memory to zero.
 *
 * @param ptr The pointer to the memory block to reallocate.
 * @param old_size The old size of the memory block.
 * @param new_size The new size of the memory block.
 * @return void* The reallocated memory block with new portions set to zero, or
 *               NULL if allocation fails.
 */
void				*ft_recalloc(void *ptr, size_t old_size, size_t new_size);

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// Char /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks if a character is alphanumeric.
 *
 * @param c Character to check.
 * @return bool True if character is a letter (lowercase or uppercase) or a
 *              digit, otherwise False.
 */
bool				ft_isalnum(char c);

/**
 * @brief Checks if a character is alphabetic.
 *
 * @param c Character to check.
 * @return bool True if character is a letter (lowercase or uppercase),
 *              otherwise False.
 */
bool				ft_isalpha(char c);

/**
 * @brief Checks if a character is part of the ASCII character set.
 *
 * @param c Character to check.
 * @return bool True if character is in the ASCII range (0-127), otherwise False
 */
bool				ft_isascii(char c);

/**
 * @brief Checks if a character is a digit.
 *
 * @param c Character to check.
 * @return bool True if character is a decimal digit ('0'-'9'), otherwise False.
 */
bool				ft_isdigit(char c);

/**
 * @brief Checks if a character is printable.
 *
 * @param c Character to check.
 * @return bool True if character is printable (32-126), otherwise False.
 */
bool				ft_isprint(char c);

/**
 * @brief Checks if a character is a whitespace.
 *
 * @param c Character to check.
 * @return bool True if character is a space, tab, newline, vertical tab,
 *              form feed, or carriage return, otherwise False.
 */
bool				ft_isspace(char c);

/**
 * @brief Converts an uppercase letter to lowercase.
 *
 * @param c Character to convert.
 * @return int The lowercase equivalent if c is uppercase, otherwise c
 *             unchanged.
 */
int					ft_tolower(char c);

/**
 * @brief Converts a lowercase letter to uppercase.
 *
 * @param c Character to convert.
 * @return int The uppercase equivalent if c is lowercase, otherwise c unchanged
 */
int					ft_toupper(char c);

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// String ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Outputs a string followed by a newline to the specified file
 *        descriptor.
 *
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
 * @return void
 */
void				ft_putendl_fd(const char *s, int fd);

/**
 * @brief Outputs a character to the specified file descriptor.
 *
 * @param c The character to output.
 * @param fd The file descriptor on which to write.
 * @return void
 */
void				ft_putchar_fd(char c, int fd);

/**
 * @brief Outputs a string to the specified file descriptor.
 *
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
 * @return void
 */
void				ft_putstr_fd(char *s, int fd);

/**
 * @brief Outputs an integer to the specified file descriptor.
 *
 * @param n The integer to output.
 * @param fd The file descriptor on which to write.
 * @return void
 */
void				ft_putnbr_fd(int n, int fd);

/**
 * @brief Locates the first occurrence of a character in a string.
 *
 * @param s String to search in.
 * @param c Character to search for.
 * @return char* Pointer to the first matching character, or NULL if not found.
 */
char				*ft_strchr(const char *s, char c);

/**
 * @brief Compares two strings lexicographically.
 *
 * This function compares the null-terminated strings @p s1 and @p s2 using
 * unsigned characters. The comparison is not affected by locale settings
 * (see strcoll() for locale-aware comparison).
 *
 * @param s1 Pointer to the first string.
 * @param s2 Pointer to the second string.
 * @return int Integer less than, equal to, or greater than zero if @p s1 is
 *             found, respectively, to be less than, to match, or be greater
 *             than @p s2.
 */
int					ft_strcmp(const char *s1, const char *s2);

/**
 * @brief Creates a duplicate of a string.
 *
 * @param s String to duplicate.
 * @return char* Newly allocated copy of the string, or NULL if allocation
 *         fails.
 */
char				*ft_strdup(const char *s);

/**
 * @brief Appends a string to another with size limitation and NUL-termination.
 *
 * @param dst Destination string.
 * @param src Source string to append.
 * @param size Size of the destination buffer.
 * @return unsigned long Total length of the string tried to create
 *                       (strlen(src) + strlen(dst)).
 *
 * @note Will append at most size-strlen(dst)-1 bytes and NUL-terminate the
 *       result.
 */
unsigned long		ft_strlcat(char *dst, const char *src, unsigned long size);

/**
 * @brief Copies a string with size limitation and NUL-termination.
 *
 * @param dst Destination buffer.
 * @param src Source string to copy.
 * @param size Size of the destination buffer.
 * @return unsigned long Total length of the string tried to create
 *                       (strlen(src)).
 *
 * @note Will copy at most size-1 bytes and NUL-terminate the result.
 */
unsigned long		ft_strlcpy(char *dst, const char *src, unsigned long size);

/**
 * @brief Calculates the length of a null-terminated string.
 *
 * Optimized implementation using word-aligned reads and bitwise operations
 * with magic numbers for performance.
 *
 * @param str Pointer to the null-terminated string.
 * @return The number of characters in @p str, excluding the null terminator.
 */
unsigned long		ft_strlen(const char *str);

/**
 * @brief Compares up to n characters of two strings.
 *
 * This function compares the first @p n bytes of the strings @p s1 and @p s2.
 * The comparison is done using unsigned characters. It is not affected by the
 * current locale (for locale-aware comparison, see strcoll()).
 *
 * @param s1 Pointer to the first string.
 * @param s2 Pointer to the second string.
 * @param n Maximum number of bytes to compare.
 * @return int Integer less than, equal to, or greater than zero if @p s1 is
 *             found, respectively, to be less than, to match, or be greater
 *             than @p s2.
 */
int					ft_strncmp(const char *s1, const char *s2, unsigned long n);

/**
 * @brief Locates a substring within a string with length limitation.
 *
 * @param big String to search in.
 * @param little Substring to search for.
 * @param len Maximum characters to search.
 * @return char* Pointer to first occurrence of little in big, or NULL if not
 *               found.
 *               Returns big if little is empty.
 */
char				*ft_strnstr(const char *big, const char *little,
						unsigned long len);

/**
 * @brief Locates the last occurrence of a character in a string.
 *
 * @param s String to search in.
 * @param c Character to search for.
 * @return char* Pointer to the last matching character, or NULL if not found.
 */
char				*ft_strrchr(const char *s, char c);

/**
 * @brief Applies a function to each character of a string with its index.
 *
 * @param s The string to process.
 * @param f The function to apply to each character (takes index and char
 *          pointer).
 */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * @brief Splits a string into an array of substrings using a delimiter.
 *
 * @param str String to split.
 * @param c Character to use as delimiter.
 * @return char** Array of strings ending with a NULL pointer.
 *                Returns an array containing only the original string if
 *                delimiter not found.
 *                Returns NULL if allocation fails.
 */
char				**ft_split(char *str, char c);

/**
 * @brief Concatenates two strings into a new string.
 *
 * @param s1 Prefix string.
 * @param s2 Suffix string.
 * @return char* New string with s1+s2, or NULL if allocation fails.
 */
char				*ft_strjoin(const char *s1, const char *s2);

/**
 * @brief Creates a new string by applying a function to each character.
 *
 * @param s The string to process.
 * @param f The function to apply to each character (takes index and char).
 * @return char* New string with results of function applications, or NULL if
 *               allocation fails.
 */
char				*ft_strmapi(const char *s, char (*f)(unsigned long, char));

/**
 * @brief Removes specified characters from the beginning and end of a string.
 *
 * @param s1 String to be trimmed.
 * @param set Set of characters to remove from both ends.
 * @return char* Newly allocated trimmed string, or NULL if allocation fails.
 */
char				*ft_strtrim(const char *s1, const char *set);

/**
 * @brief Creates a substring from a string.
 *
 * @param s The source string.
 * @param start The starting index of the substring.
 * @param len The maximum length of the substring.
 * @return char* Newly allocated substring, or NULL if allocation fails.
 */
char				*ft_substr(const char *s, unsigned int start,
						unsigned long len);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// String <-> Number///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Converts a string to an integer (atoi implementation).
 *
 * @param str The string to convert to an integer.
 *           Leading whitespace is ignored.
 *           The function processes optional '+' or '-' sign followed by digits.
 *           Parsing stops at the first non-digit character.
 * @return The converted integer value if successful.
 * @return 0 if the conversion fails or if the value exceeds INT_MIN/INT_MAX.
 *
 * @note This function calls ft_atol internally and performs bounds checking.
 */
int					ft_atoi(const char *nptr);

/**
 * @brief Converts a string to a long integer.
 *
 * @param str String to convert.
 * @return long The converted long value.
 *              Returns 0 if no valid conversion could be performed.
 *              Returns LONG_MAX/LONG_MIN in case of overflow/underflow.
 */
long				ft_atol(const char *nptr);

/**
 * @brief Converts a string to an unsigned long integer.
 *
 * Parses the string @p str and returns its value as an unsigned long integer.
 * Leading whitespace is skipped, and an optional '+' sign is supported.
 * The function stops at the first non-digit character encountered after
 * processing any leading whitespace and optional sign.
 *
 * @param str Pointer to the null-terminated string to convert.
 * @return The converted value as an unsigned long. Returns 0 if no valid
 *         conversion could be performed or if the string is empty.
 * @note This function does not handle the '-' sign as it returns an unsigned
 *       value.
 * @note No overflow checking is performed; if the represented value exceeds
 *       ULONG_MAX, the result is undefined.
 */
unsigned long		ft_atoul(const char *str);

/**
 * @brief Converts an integer to a string.
 *
 * @param n Integer to convert.
 * @return char* Newly allocated string containing the number, or NULL if
 *               allocation fails.
 *
 * @note Handles negative numbers. Caller must free the returned string.
 */
char				*ft_itoa(int n);

/**
 * @brief Converts an integer to a string using the specified base.
 *
 * @param n Integer to convert.
 * @param b String representing the base characters to use.
 * @return char* Newly allocated string containing the number in the given base,
 *               or NULL if allocation fails.
 *
 * @note Handles negative numbers. Caller must free the returned string.
 */
char				*ft_itoa_base(int n, const char *b);

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// Math /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Computes the absolute value of a long integer.
 *
 * @param n The long integer whose absolute value is to be computed.
 * @return The absolute value of the input long integer.
 */
long				ft_abs(long n);

/**
 * @brief Finds an absolute number
 *
 * @param n Number
 * @return float Absolute value of n
 */
double				ft_fabs(double n);

/**
 * Comparing floats with == or != is dangerous because of floating point
 * precision. This function checks if two floats are equal within a certain
 * epsilon range.
 *
 * @param a First float to compare
 * @param b Second float to compare
 * @return bool Equality result
 *
 * @see	https://stackoverflow.com/a/32334103
 */
bool				ft_feq(double a, double b);

/**
 * @brief Finds the maximum of two doubles.
 *
 * @param a The first double.
 * @param b The second double.
 * @return long The larger of the two input values.
 */
double				ft_fmax(double a, double b);

/**
 * @brief Finds the maximum of two longs.
 *
 * @param a The first long.
 * @param b The second long.
 * @return long The larger of the two input values.
 */
long				ft_max(long a, long b);

/**
 * @brief Returns the minimum of two longs.
 *
 * @param a The first long.
 * @param b The second long.
 * @return long The smaller of the two input values.
 */
long				ft_min(long a, long b);

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// Extra ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Searches for a variable in the environment.
 *
 * @param envp The environment array to search in.
 * @param var The variable to search for (must end with '=').
 * @return char* Pointer to the found environment variable string, or NULL if
 *         not found.
 *
 * @warning The searched variable *must* end with a '='.
 */
char				*ft_env_find(char **envp, const char *var);

#endif
