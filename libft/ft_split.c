/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:22:13 by gcassi-d          #+#    #+#             */
/*   Updated: 2025/09/28 16:49:20 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(char const *src, unsigned int n)
{
	unsigned int	i;
	char			*dest;

	dest = malloc(sizeof(char) * (n + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	ft_sections(char const *str, char c)
{
	int	n;
	int	check;

	n = 0;
	check = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		while (*str && *str != c)
		{
			check = 1;
			str++;
		}
		if (check)
			n += 1;
		check = 0;
	}
	return (n);
}

static char	**ft_actual(char **split, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (!split[i])
		{
			i = 0;
			while (i < size)
			{
				if (split[i])
					free(split[i]);
				i++;
			}
			free(split);
			return (NULL);
		}
		i++;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char			**result;
	char const		*aux;
	unsigned int	n;
	int				i;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (ft_sections(s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		n = 0;
		aux = s;
		while (*s && *s++ != c)
			n++;
		if (n)
			result[i++] = ft_strndup(aux, n);
	}
	result[i] = NULL;
	return (ft_actual(result, i));
}
