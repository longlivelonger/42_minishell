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

#ifndef SYNTAX_TREE_H
# define SYNTAX_TREE_H

typedef struct s_command
{
	char	*command_path;
	char	is_path_alloc;
	char	**args_array;
	char	*in;
	int		in_flag;
	char	*out;
	int		out_flag;
}	t_com;

typedef struct s_job
{
	struct s_command	*com;
	struct s_job		*next_job;	
}	t_job;

typedef struct s_command_line
{
	struct s_job			*job;
	struct s_command_line	*and_cl;
	struct s_command_line	*semicolon_cl;	
}	t_cl;

t_cl	*parse_command_line(t_list *token_list);
int		execute_syntax_tree(t_cl *current_cl);
int		find_command(char **path_name, char **com_name, char *isa);
int		parse_n_execute(char *str);
void	free_syntax_tree(t_cl *cl);
void	free_kostyl(t_com *com);
int		ext_close(int fd);
int		ext_pipe_close(int pipe[2], int	end_to_close);
int		open_input_stream(char *file, int fd, int in_flag);
int		open_output_stream(char *file, int fd, int out_flag);
int		dup_redirected_io(int (fd_pipe)[2], int *fd_pipe_out,
			int *fd_pipe_in, t_job *is_next_job);
int		open_here_doc(char *delim);
int		read_file_err(t_com *command, int *fd_out, int *fd_in);
int		launch_buildin(char **args);
int		command_nfound_err(char *name);
int		check_exit_status(int exit_status, int launch_return);
int		ft_strcmp_u(char *str1, char *str2);

#endif
