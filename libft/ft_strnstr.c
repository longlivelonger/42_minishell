/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stanislavkomin <stanislavkomin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:10:47 by stanislavko       #+#    #+#             */
/*   Updated: 2021/10/12 16:29:59 by stanislavko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = -1;
	if (needle[0] == '\0')
		return (haystack);
	while (++i < len && haystack[i] != '\0')
	{
		if (haystack[i] != needle[0])
			continue ;
		j = i + 1;
		while (j < len && haystack[j] != '\0' && needle[j - i] != '\0'
			&& haystack[j] == needle[j - i])
			j++;
		if (needle[j - i] == '\0')
			return (haystack + i);
	}
	return (0);
}
