/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:01:42 by gcassi-d          #+#    #+#             */
/*   Updated: 2025/09/20 14:06:56 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in(char const *s1, char c, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (s1[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	set_size;
	size_t	start;
	char	*new;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	set_size = ft_strlen(set);
	while (s1[start] && ft_in(set, s1[start], set_size))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && ft_in(set, s1[end], set_size))
		end--;
	new = malloc((end - start + 2) * sizeof(char));
	if (!new)
		return (NULL);
	ft_memcpy(new, s1 + start, end - start + 1);
	new[end - start + 1] = 0;
	return (new);
}
