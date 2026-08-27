/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:28:35 by gcassi-d          #+#    #+#             */
/*   Updated: 2025/09/26 10:20:12 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	len = 0;
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	if (size > dest_len)
		len = dest_len + src_len;
	else
		len = src_len + size;
	while (size > (dest_len + 1) && src[i])
	{
		dst[dest_len] = src[i];
		i++;
		dest_len++;
	}
	dst[dest_len] = '\0';
	return (len);
}
