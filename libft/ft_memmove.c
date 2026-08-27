/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:12:23 by gcassi-d          #+#    #+#             */
/*   Updated: 2025/09/26 19:50:23 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;

	if (!dest && !src)
		return (dest);
	if (src <= dest)
	{
		i = n - (size_t)(dest - src) - 1;
		while (++i < n)
			((char *)dest)[i] = ((char *)src)[i];
		i = -1;
		while (++i < n - (size_t)(dest - src) && i < n)
			((char *)dest)[i] = ((char *)src)[i];
	}
	else
	{
		i = -1;
		while (++i < n)
			((char *)dest)[i] = ((char *)src)[i];
	}
	return (dest);
}
