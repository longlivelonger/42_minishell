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

int	check_syntax(t_list *token_list)
{
	char	lt;
	int		is_err;

	lt = 0;
	is_err = 0;
	while (token_list && is_err != 1)
	{
		if (((t_token *)token_list->content)->type == '|' && (lt == '|' || !lt))
			is_err = 1;
		if ((lt == '>' || lt == '<' || lt == 'L' || lt == 'G')
				&& ((t_token *)token_list->content)->type != 'W')
			is_err = 1;
		lt = ((t_token *)token_list->content)->type;
		token_list = token_list->next;
	}
	if (is_err || (lt == '>' || lt == '<' || lt == 'L' || lt == 'G'))
	{
		is_err = 1;
		write(2, "-bash: syntax error near unexpected token `", 43);
		write(2, &lt, 1);
		write(2, "'\n", 2);
	}
	return (is_err);
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
	char	*value;

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
