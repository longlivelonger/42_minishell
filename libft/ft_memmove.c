/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stanislavkomin <stanislavkomin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:10:47 by stanislavko       #+#    #+#             */
/*   Updated: 2021/10/12 16:11:40 by stanislavko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	size_t	diff;

	if (dst == 0 && src == 0)
		return (dst);
	i = 0;
	while (i < len)
	{
		if (src > dst)
			diff = i;
		else
			diff = len - i - 1;
		*(unsigned char *)(dst + diff) = *(unsigned char *)(src + diff);
		i++;
	}
	return (dst);
}
