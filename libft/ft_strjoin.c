/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:00:21 by gcassi-d          #+#    #+#             */
/*   Updated: 2025/09/17 11:00:06 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	new = malloc(sizeof(char) * (1 + ft_strlen(s1) + ft_strlen(s2)));
	if (!new)
		return (NULL);
	new[0] = 0;
	if (1 + ft_strlen(s1) + ft_strlen(s2) == 1)
		return (new);
	ft_strlcat(new, s1, 1 + ft_strlen(s1));
	ft_strlcat(new, s2, 1 + ft_strlen(s2) + ft_strlen(s1));
	return (new);
}
