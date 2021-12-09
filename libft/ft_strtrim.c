/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stanislavkomin <stanislavkomin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:10:47 by stanislavko       #+#    #+#             */
/*   Updated: 2021/10/12 17:00:58 by stanislavko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isinset(char c, char const *set)
{
	int	i;

	i = -1;
	while (set[++i] != '\0')
		if (c == set[i])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	if (s1 == 0 || set == 0)
		return (0);
	start = 0;
	while (isinset(s1[start], set) && s1[start] != '\0')
		start++;
	end = start;
	while (s1[end] != '\0')
		end++;
	end--;
	while (isinset(s1[end], set) && end > start)
		end--;
	str = malloc((end - start + 2) * sizeof(*str));
	if (str == 0)
		return (0);
	i = -1;
	while (start + ++i <= end)
		str[i] = s1[start + i];
	str[i] = '\0';
	return (str);
}
