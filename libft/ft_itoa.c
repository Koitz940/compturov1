/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:47:14 by gcassi-d          #+#    #+#             */
/*   Updated: 2025/09/18 11:16:53 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	digits(long m)
{
	size_t	size;

	size = 1;
	if (m == 0)
		return (2);
	if (m < 0)
	{
		size++;
		m = -m;
	}
	while (m > 0)
	{
		m /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*num;
	long	m;
	size_t	size;
	size_t	i;

	m = n;
	size = digits(m);
	num = malloc(size * sizeof(char));
	if (!num)
		return (NULL);
	i = size - 2;
	if (m < 0)
	{
		m = -m;
		num[0] = '-';
	}
	if (m == 0)
		num[0] = '0';
	while (m > 0)
	{
		num[i--] = '0' + m % 10;
		m /= 10;
	}
	num[size - 1] = 0;
	return (num);
}
