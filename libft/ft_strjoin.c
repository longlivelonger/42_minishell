/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stanislavkomin <stanislavkomin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:10:47 by stanislavko       #+#    #+#             */
/*   Updated: 2021/10/12 16:58:12 by stanislavko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	int		i;
	char	*str;

	if (s1 == 0 || s2 == 0)
		return (0);
	s1_len = 0;
	while (s1[s1_len] != '\0')
		s1_len++;
	s2_len = 0;
	while (s2[s2_len] != '\0')
		s2_len++;
	str = malloc((s1_len + s2_len + 1) * sizeof(*str));
	if (str == 0)
		return (0);
	i = -1;
	while (++i < s1_len)
		str[i] = s1[i];
	i--;
	while (++i < (s1_len + s2_len))
		str[i] = s2[i - s1_len];
	str[s1_len + s2_len] = '\0';
	return (str);
}
