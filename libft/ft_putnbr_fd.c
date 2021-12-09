/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stanislavkomin <stanislavkomin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:10:47 by stanislavko       #+#    #+#             */
/*   Updated: 2021/10/12 15:26:48 by stanislavko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		digit;
	char	c;

	if (n < 0)
		write(fd, "-", 1);
	digit = n % 10;
	if (n < 0)
		digit *= -1;
	c = '0' + digit;
	if (n <= -10)
		ft_putnbr_fd((n / 10) * -1, fd);
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	write(fd, &c, 1);
}
