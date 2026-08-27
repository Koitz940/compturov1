/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:48:07 by gcassi-d          #+#    #+#             */
/*   Updated: 2025/09/20 20:47:55 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*cpy;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s + start);
	if (size > len)
		size = len;
	if (ft_strlen(s) < start)
		size = 0;
	cpy = malloc(sizeof(char) * (1 + size));
	if (!cpy)
		return (NULL);
	ft_memcpy(cpy, s + start, size);
	cpy[size] = 0;
	return (cpy);
}
