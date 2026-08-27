/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:59:05 by gcassi-d          #+#    #+#             */
/*   Updated: 2025/09/26 19:48:05 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*p;
	char	*q;

	if (!dest && !src)
		return (dest);
	p = (char *)src;
	q = (char *)dest;
	i = 0;
	while (i < n)
	{
		q[i] = p[i];
		i++;
	}
	return (dest);
}
