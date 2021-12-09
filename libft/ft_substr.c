/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stanislavkomin <stanislavkomin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:10:47 by stanislavko       #+#    #+#             */
/*   Updated: 2021/10/13 14:45:25 by stanislavko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	size;

	if (s == 0)
		return (0);
	size = len;
	if (len + start > ft_strlen(s))
		size = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		size = 0;
	str = malloc((size + 1) * sizeof(*str));
	if (str == 0)
		return (0);
	i = -1;
	while (++i < size && s[start + i] != '\0')
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}
