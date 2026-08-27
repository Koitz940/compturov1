/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:13:33 by gcassi-d          #+#    #+#             */
/*   Updated: 2025/09/26 10:19:58 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*p;

	p = malloc(sizeof(const char) * (1 + ft_strlen(s)));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s, 1 + ft_strlen(s));
	return (p);
}
