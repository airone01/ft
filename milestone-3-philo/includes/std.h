/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:54:48 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 13:47:03 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STD_H
# define STD_H

# include <aio.h>
# include <limits.h>
# include <stdbool.h>

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
unsigned long	ft_atoul(const char *str);

/**
 * @brief Allocates zero-initialized memory for an array.
 *
 * This function allocates memory for an array of @p nmemb elements, each of
 * @p size bytes, and initializes all bytes in the allocated memory to zero.
 *
 * @param nmemb Number of elements.
 * @param size Size of each element in bytes.
 * @return A pointer to the allocated zero-initialized memory, or NULL if the
 *         allocation fails or an overflow occurs.
 */
void			*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief Checks if a character is a decimal digit (0–9).
 *
 * @param c Character to check.
 * @return true if @p c is a decimal digit, false otherwise.
 */
bool			ft_isdigit(char c);

/**
 * @brief Checks if a character is a space character.
 *
 * Returns true if @p c is a space character (e.g., ' '), false otherwise.
 *
 * @param c Character to check.
 * @return true if @p c is a space character, false otherwise.
 */
bool			ft_isspace(char c);

/**
 * @brief Calculates the length of a null-terminated string.
 *
 * Optimized implementation using word-aligned reads and bitwise operations
 * with magic numbers for performance.
 *
 * @param str Pointer to the null-terminated string.
 * @return The number of characters in @p str, excluding the null terminator.
 */
unsigned long	ft_strlen(const char *str);

/**
 * @brief Compares two strings lexicographically.
 *
 * This function compares the null-terminated strings @p s1 and @p s2 using
 * unsigned characters. The comparison is not affected by locale settings
 * (see strcoll() for locale-aware comparison).
 *
 * @param s1 Pointer to the first string.
 * @param s2 Pointer to the second string.
 * @return An integer less than, equal to, or greater than zero if @p s1 is
 *         found, respectively, to be less than, to match, or be greater than
 *         @p s2.
 */
int				ft_strcmp(const char *s1, const char *s2);

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
 * @return An integer less than, equal to, or greater than zero if @p s1 is
 *         found, respectively, to be less than, to match, or be greater than
 *         @p s2.
 */
int				ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
