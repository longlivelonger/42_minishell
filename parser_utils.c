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

int	ft_strlen_adpt(char	*str)
{
	int	count;

	if (!str)
		return (0);
	count = 0;
	while (*(str + count))
		count++;
	return (count);
}

int	extract_key(char *str)
{
	int	count;

	count = 0;
	while (*(str + count) && *(str + count) != '=')
		count++;
	return (count);
}

int	write_env_value(char *key, char *dst, int *dst_count)
{
	int		key_len;
	int		value_len;
	//char	*key;
	char	*value;
	//char	*fake_env[3];

	//fake_env[0] = "PATH=/usr/bin:/123/123:test";
	//fake_env[1] = "test=proverka123";
	//fake_env[2] = "op=opaopaopapapa";
	key_len = 0;
	if ((key + key_len) && (*(key +key_len) == '?'))
	{
		*(dst + *dst_count) = g_global.exit_status + '0';
		(*dst_count)++;
		return (1);
	}
	while ((key + key_len) && ((*(key + key_len) >=  97 && *(key + key_len) <= 122) ||
		(*(key + key_len) >=  65 && *(key + key_len) <= 90)))
		key_len++;
	if (key_len == 0)
		return (0);
	key = ft_substr(key, 0, key_len);
	value = get_env(key);
	value_len = 0;
	if (value)
	{
		while (*(value + value_len))
		{
			*(dst + *dst_count) = *(value + value_len);
			(*dst_count)++;
			value_len++;
		}
	}
	free(key);
	return (key_len);
}


void	adv_str_write(char *str, char *dst, int max_count)
{
	int		count;
	int		dst_count;
	char	term_symbol;

	count = 0;
	(void)max_count;
	dst_count = 0;
	term_symbol = '\0';
	while(*(str + count) && (term_symbol || (!check_special_symbol(&str) && *(str + count) != ' ' && *(str + count) != '	')))
	{
		if (*(str + count) == '"' || *(str + count) == 39)
		{
			if (*(str + count) == term_symbol)
				term_symbol = '\0';
			else if (!term_symbol)
				term_symbol = check_quoted_sequence(str + count);
		}
		else if (*(str + count) == '$' && term_symbol != 39)
			count += write_env_value(str + count + 1, dst, &dst_count);
		else
		{
			*(dst + dst_count) = *(str + count);
			dst_count++;
		}
		count++;
	}
	*(dst + dst_count) = '\0';
}