/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dweeper <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:22:15 by dweeper           #+#    #+#             */
/*   Updated: 2021/12/09 18:19:27 by dweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_TREE_H
# define S_TREE_H

typedef struct	s_command
{
	char	*command_path;
	char	**args_array;
	char	*in;
	char	*out;
}	t_com;

typedef struct	s_job
{
	struct s_command	*com;
	struct s_job		*next_job;	
}	t_job;

typedef struct	s_command_line
{
	struct s_job			*job;
	struct s_command_line	*and_cl;
	struct s_command_line	*semicolon_cl;	
}	t_cl;

t_cl	*parse_command_line(t_list *token_list);
int		execute_syntax_tree(t_cl *current_cl);
int		parse_n_execute(char *str);
void	free_syntax_tree(t_cl *cl);
int		ext_close(int fd);
int		ext_pipe_close(int pipe[2], int	end_to_close);
int		ext_open(char *file, int fd, int end_to_open);

#endif