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

static t_token	*create_token(char *value, char type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	new_token->flag = 0;
	return (new_token);
}

static int	get_word(char **str, char **dst)
{
	int		count;
	int		env_count;
	char	term_symbol;

	env_count = 0;
	count = 0;
	term_symbol = '\0';
	//printf("%d \n", count);
	while(*(*str + count) && (term_symbol || (!check_special_symbol(str) && *(*str + count) != ' ' && *(*str + count) != '	')))
	{
		if (*(*str + count) == '"' || *(*str + count) == 39)
		{
			if (*(*str + count) == term_symbol)
				term_symbol = '\0';
			else if (!term_symbol)
			{
				term_symbol = check_quoted_sequence(*str + count);
				if (!term_symbol)
					env_count++;
			}
		}
		else if (*(*str + count) == '$' && term_symbol != 39)
			env_count += count_env_value(*str + count + 1, &count);
		else
			env_count++;
		count++;
		//env_count++;
	}
	//printf("%d %d\n", count, env_count);
	*dst = malloc(sizeof(char) * (1 + env_count));
	if (!(*dst))
		return (-1);
	adv_str_write(*str, *dst, count);
	//printf("%s!\n", *dst);
	//ft_strlcpy(new_word, *str, count + 1);
	//*dst = new_word;
	return (count);
}

char	check_special_symbol(char** str)
{
	if (**str == '|')
		return ('|');
	//else if (**str == '$')
	//	return (ENV);
	//else if (**str == 39)
	//	return (S_QUOTE);
	//else if (**str == '"')
	//	return (D_QUOTE);
	else if (**str == '<')
	{
		if ((*str + 1) && *(*str + 1) == '<')
			return (REDIR_FROM_UNT);
		else
			return (REDIR_FROM);
	}
	else if (**str == '>')
	{
		if ((*str + 1) && *(*str + 1) == '>')
			return (REDIR_TO_APP);
		else
			return (REDIR_TO);
	}
	return (0);
}

static t_list	*get_token(char **str)
{
	t_token	*new_token;
	char	token_type;
	char	*value;
	int		count;

	count = 1;
	value = NULL;
	while (**str == ' ' || **str == '	')
		(*str)++;
	token_type = check_special_symbol(str);
	if (token_type == 'G' || token_type == 'L')
		count++;
	if (!token_type)
	{
		count = get_word(str, &value);
		token_type = WORD;
	}
	*str += count;
	new_token = create_token(value, token_type);
	return (ft_lstnew(new_token));
}

t_list	*split_to_tokens(char *str)
{
	t_list	*new_token;
	t_list	*token_list;

	token_list = NULL;
	while (*str)
	{
		new_token = get_token(&str);
		ft_lstadd_back(&token_list, new_token);
	}
	return (token_list);
}
