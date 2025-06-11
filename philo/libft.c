/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:01:10 by isainz-r          #+#    #+#             */
/*   Updated: 2024/10/29 12:01:12 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Compares two strings up to n characters.
 *
 * @param s1 Pointer to the first string.
 * @param s2 Pointer to the second string.
 * @param n Maximum number of characters to compare.
 * @return Difference between the first differing characters,
 *         or 0 if equal up to n.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n)
		i++;
	if (i == n)
		i--;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/**
 * @brief Trims characters from the beginning and end of a string.
 *
 * Removes all characters in the set from the start and end of s1.
 *
 * @param s1 The string to be trimmed.
 * @param set The set of characters to remove.
 * @return A new trimmed string, or NULL on allocation failure.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	char	*new_string;

	i = 0;
	while (ft_strchr(set, s1[i]) != 0 && s1[i] != '\0')
		i++;
	start = i;
	i = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) != 0 && i != 0)
		i--;
	new_string = ft_substr(s1, start, i - start + 1);
	return (new_string);
}

/**
 * @brief Searches for the first occurrence of a character in a string.
 *
 * @param s Pointer to the string to search.
 * @param c Character to find.
 * @return Pointer to the first occurrence of c, or NULL if not found.
 */
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if ((char)c == '\0')
		return ((char *) &s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *) &s[i]);
		i++;
	}
	return (0);
}

/**
 * @brief Calculates the length of a string.
 *
 * @param s Pointer to the string.
 * @return The number of characters before the null terminator.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * @brief Extracts a substring from a string.
 *
 * Allocates and returns a substring starting at index 'start' with a max
 * length of 'len'.
 *
 * @param s The original string.
 * @param start The start index of the substring.
 * @param len The maximum length of the substring.
 * @return A pointer to the new substring, or NULL on allocation failure.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub_string;

	if (start > ft_strlen(s) || s[0] == '\0' || len == 0)
	{
		sub_string = malloc(1 * sizeof(char));
		if (sub_string == NULL)
			return (NULL);
		sub_string[0] = '\0';
		return ((char *)sub_string);
	}
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	sub_string = malloc(len + 1 * sizeof(char));
	if (!sub_string)
		return (NULL);
	i = 0;
	while (i < len)
		sub_string[i++] = s[start++];
	sub_string[i] = '\0';
	return ((char *)sub_string);
}
