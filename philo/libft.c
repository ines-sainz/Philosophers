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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

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
