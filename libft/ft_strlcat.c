/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stanislavkomin <stanislavkomin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:10:47 by stanislavko       #+#    #+#             */
/*   Updated: 2021/10/12 15:19:02 by stanislavko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;

	if (dstsize == 0)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	i = dst_len;
	if (dst_len >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (src[i - dst_len] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i - dst_len];
		i++;
	}
	if (dst_len < dstsize)
		dst[i] = '\0';
	return (ft_strlen(src) + dst_len);
}
