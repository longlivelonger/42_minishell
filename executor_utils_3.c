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

#include	"minishell.h"

int	ft_strcmp_u(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (0);
		str1++;
		str2++;
	}
	if (*str1 != *str2)
		return (0);
	return (1);
}

static void	write_file_err(char *name)
{
	write(2, "minishell: ", 11);
	write(2, name, ft_strlen(name));
	perror(": ");
}

int	read_file_err(t_com *command, int *fd_out, int *fd_in)
{
	errno = 0;
	*fd_in = open_input_stream(command->in, *fd_in, command->in_flag);
	if (errno)
		write_file_err(command->in);
	else
	{
		*fd_out = open_output_stream(command->out, *fd_out, command->out_flag);
		if (errno)
			write_file_err(command->in);
	}
	if (errno)
	{
		ext_close(*fd_in);
		ext_close(*fd_out);
		return (1);
	}
	return (0);
}

char	term_symbol_kost(char *str, char term_symbol)
{
	if (*str == term_symbol)
		return ('\0');
	else if (!term_symbol)
		return (check_quoted_sequence(str));
	return (term_symbol);
}

int	is_letter(char c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}
