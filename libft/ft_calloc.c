/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:55:26 by gcassi-d          #+#    #+#             */
/*   Updated: 2025/09/20 13:13:29 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (!nmemb || !size)
		return (malloc(0));
	if ((nmemb * size) / size != nmemb)
		return (NULL);
	p = malloc(size * nmemb);
	if (!p)
		return (NULL);
	ft_bzero(p, size * nmemb);
	return (p);
}
