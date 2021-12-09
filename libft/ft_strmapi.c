/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stanislavkomin <stanislavkomin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:10:47 by stanislavko       #+#    #+#             */
/*   Updated: 2021/10/12 17:01:32 by stanislavko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;
	unsigned int	len;

	if (s == 0)
		return (0);
	len = ft_strlen(s);
	str = malloc((len + 1) * sizeof(*str));
	if (str == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
