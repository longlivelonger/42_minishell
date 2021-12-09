/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stanislavkomin <stanislavkomin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:10:47 by stanislavko       #+#    #+#             */
/*   Updated: 2021/10/13 14:05:10 by stanislavko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	int		n_copy;

	size = 0;
	if (n <= 0)
		size++;
	n_copy = n;
	while (n != 0 && ++size)
		n /= 10;
	str = malloc((size + 1) * sizeof(*str));
	if (str == 0)
		return (0);
	str[size] = '\0';
	n = n_copy;
	while (size > 0)
	{
		str[--size] = my_abs(n_copy % 10) + '0';
		n_copy /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
