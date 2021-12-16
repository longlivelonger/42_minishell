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

char	*extract_key(char *str)
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
	//(*count)++;
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


adv_str_write(char *dst, char *src, int max_count)
{
	int		count;
	int		dst_count;
	int		is_quoted;
	char	*new_word;
	char	term_symbol;

	count = 0;
	dst_count = 0;
	*token_flag = 0;
	is_quoted = 0;
	term_symbol = '\0';

	while(*(src + count) != '\0' && *(src + count) != ' ' && *(src + count) != '	')))
{
	if (*(src + count) == '"' || *(src + count) == 39)
	{
		if (*(src + count) == term_symbol)
			term_symbol = '\0';
		else if (!term_symbol)
		{
			term_symbol = check_quoted_sequence(*str + count);
			if (!term_symol)
			{
				*(dst + dst_count) = *(src + count);
				dst_count++;
			}
		}
	}
	else if (*(src + count) == '$' && term_symbol != 39)
		count += write_env_value(src + count + 1, dst, &dst_count);
	else
	{
		*(dst + dst_count) = *(src + count);
		dst_count++;
	}
	count++;
	}
}