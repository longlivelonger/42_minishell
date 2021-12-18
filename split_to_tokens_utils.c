/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dweeper <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:54:29 by dweeper           #+#    #+#             */
/*   Updated: 2021/12/09 17:17:26 by dweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_quoted_sequence(char* str)
{
	char	q_type;

	q_type = *str;
	while(*str)
	{
		str++;
		if (*str == q_type)
			return (q_type);
	}
	return ('\0');
}

int	check_syntax(t_list *token_list);


int	count_env_value(char *key, int *count)
{
	int		key_len;
	int		value_len;
	//char	*key_name;
	char	*value;
	//char	*fake_env[3];

	//fake_env[0] = "PATH=/usr/bin:/123/123:test";
	//fake_env[1] = "test=proverka123";
	//fake_env[2] = "op=opaopaopapapa";
	//(*count)++;
	key_len = 0;
	if ((key + key_len) && ((*(key +key_len) >=  48 && *(key + key_len) <= 57)))
		return (1);
	while ((key + key_len) && ((*(key +key_len) >=  97 && *(key + key_len) <= 122) ||
		(*(key + key_len) >=  65 && *(key + key_len) <= 90)))
		(key_len)++;
	*count += key_len;
	if (key_len == 0)
		return (0);
	key = ft_substr(key, 0, key_len);
	value = get_env(key);
	value_len = ft_strlen_adpt(value);
	free(key);
	return (value_len);
}
