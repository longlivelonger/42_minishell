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
	return (new_token);
}

static int	get_word(char **str, char **dst)
{
	int		count;
	char	*new_word;

	count = 0;
	while(*(*str + count) != '\0' && *(*str + count) != '|' && *(*str + count) != '>' &&
			*(*str + count) != '<' && *(*str + count) != '"' && *(*str + count) != 39
			&& *(*str + count) != ' ')
	{
		count++;
	}
	new_word = malloc(sizeof(char) * (count + 1));
	if (!new_word)
		return (-1);
	ft_strlcpy(new_word, *str, count + 1);
	*dst = new_word;
	return (count);
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
	if (**str == '|')
		token_type = '|';
	else if (**str == '<')
		token_type = REDIR_FROM;
	else if (**str == '>')
		token_type = REDIR_TO;
	else
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
