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

#ifndef MINIS_PARSER_H
# define MINIS_PARSER_H

enum	token_type
{
	WORD = 1;
	PIPE = '|';
	SEMICOLON = ';';
	AMPERSAND = '&';
	REDIR_TO = '>';
	REDIR_FROM = '<';
}

typedef struct	s_token
{
	char	*value;
	char	type;
}			t_token;

#endif
