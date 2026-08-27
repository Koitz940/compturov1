/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:19:31 by gcassi-d          #+#    #+#             */
/*   Updated: 2025/09/20 20:56:20 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	m;
	size_t	p;

	if (!big || !little)
		return (NULL);
	m = ft_strlen(little);
	i = -1;
	while (++i + m <= len)
	{
		if ((big[i] == little[0] && big[i]) || !m)
		{
			j = -1;
			p = 0;
			while (++j < m)
			{
				if (big[i + j] == little[j] && big[i])
					p++;
			}
			if (p == m)
				return ((char *)(big + i));
		}
	}
	return (NULL);
}
