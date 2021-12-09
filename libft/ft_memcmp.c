/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stanislavkomin <stanislavkomin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:10:47 by stanislavko       #+#    #+#             */
/*   Updated: 2021/10/12 16:25:02 by stanislavko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && *(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i))
		i++;
	if (n == i)
		return (0);
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}
