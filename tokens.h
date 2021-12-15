/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minis_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dweeper <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:53:27 by dweeper           #+#    #+#             */
/*   Updated: 2021/12/09 18:19:22 by dweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# define WORD 'W'
# define PIPE '|'
# define SEMICOLON ';'
# define AMPERSAND '&'
# define REDIR_TO '>'
# define REDIR_TO_APP 'G'
# define REDIR_FROM '<'
# define REDIR_FROM_UNT 'L'
# define S_QUOTE 39
# define D_QUOTE '"'
# define ENV '$'

typedef struct	s_token
{
	char	*value;
	char	type;
}			t_token;

t_list	*split_to_tokens(char *str);
int		check_quoted_sequence(char* str);
void	free_token_list(t_list *tl);

#endif
