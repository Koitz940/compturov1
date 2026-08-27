/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 21:49:26 by gcassi-d          #+#    #+#             */
/*   Updated: 2025/09/27 13:36:47 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	m;
	char	c;

	m = n;
	if (m < 0)
	{
		write(fd, "-", 1);
		m = -m;
	}
	if (m > 9)
		ft_putnbr_fd(m / 10, fd);
	c = m % 10 + '0';
	ft_putchar_fd(c, fd);
}
