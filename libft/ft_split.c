/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stanislavkomin <stanislavkomin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:10:47 by stanislavko       #+#    #+#             */
/*   Updated: 2021/10/13 14:47:57 by stanislavko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	split_size(char const *s, char c)
{
	int	size;
	int	i;

	if (ft_strlen(s) <= 0)
		return (0);
	size = 0;
	i = -1;
	while (s[++i] != '\0')
	{
		if (i > 0 && s[i - 1] != c && s[i] == c)
			size++;
		else if (i > 0 && s[i] != c && s[i + 1] == '\0')
			size++;
	}
	return (size);
}

static int	has_malloc_error(char **arr, int size)
{
	int	i;

	i = -1;
	while (++i < size - 1)
		if (arr[i] == 0)
			return (1);
	return (0);
}

static char	**check_result(char **arr, int size)
{
	int	i;

	if (!has_malloc_error(arr, size))
		return (arr);
	i = -1;
	while (++i < size)
		if (arr[i] != 0)
			free(arr[i]);
	free(arr);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		size;
	int		i;
	int		start;

	if (s == 0)
		return (0);
	size = split_size(s, c);
	arr = malloc((size + 1) * sizeof(*arr));
	if (arr == 0)
		return (0);
	arr[size] = 0;
	i = -1;
	start = 0;
	size = 0;
	while (s[++i] != '\0')
	{
		if (i > 0 && s[i - 1] == c && s[i] != c)
			start = i;
		if (i > 0 && s[i - 1] != c && s[i] == c)
			arr[size++] = ft_substr(s, start, i - start);
		else if (i > 0 && s[i] != c && s[i + 1] == '\0')
			arr[size++] = ft_substr(s, start, i - start + 1);
	}
	return (check_result(arr, size));
}
