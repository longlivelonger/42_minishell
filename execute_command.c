/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_stree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dweeper <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:18:30 by dweeper           #+#    #+#             */
/*   Updated: 2021/12/09 18:19:19 by dweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	launch_command(t_com *com, int fd_in, int fd_out)
{
	pid_t	fork_return;

	if (read_file_err(com, &fd_out, &fd_in))
		return (-1);
	fork_return = find_command(&com->command_path,
			com->args_array, &com->is_path_alloc);
	if (fork_return == -1)
		fork_return = command_nfound_err(com->command_path);
	else if (!fork_return)
		fork_return = launch_buildin(com->args_array);
	else
	{
		fork_return = fork();
		if (fork_return == -1)
			perror("fork");
		else if (fork_return == 0)
		{
			execve(com->command_path, com->args_array, make_envp_array());
			perror(com->command_path);
			exit(1);
		}
	}
	ext_close(fd_in);
	ext_close(fd_out);
	return (fork_return);
}

static int	launch_job(t_job *current_job, int fd_stdout)
{
	int		fd_pipe[2];
	int		fd_pipe_out;
	int		fd_pipe_in;
	int		exit_status;
	pid_t	command_pid;

	fd_pipe_out = -1;
	fd_pipe_in = -1;
	while (current_job)
	{
		if (dup_redirected_io(fd_pipe, &fd_pipe_out,
				&fd_pipe_in, current_job->next_job))
			break ;
		if (!(current_job->next_job))
			dup2(fd_stdout, 1);
		command_pid = launch_command(current_job->com, fd_pipe_in, fd_pipe_out);
		current_job = current_job->next_job;
	}
	waitpid(command_pid, &exit_status, 0);
	return (check_exit_status(exit_status, command_pid));
}

int	execute_syntax_tree(t_cl *current_cl)
{
	t_job	*current_job;
	int		std_fd_copy[2];
	int		status;

	std_fd_copy[0] = dup(0);
	std_fd_copy[1] = dup(1);
	while (current_cl)
	{
		current_job = current_cl->job;
		status = launch_job(current_job, std_fd_copy[1]);
		dup2(std_fd_copy[0], 0);
		dup2(std_fd_copy[1], 1);
		close(std_fd_copy[0]);
		close(std_fd_copy[1]);
		if (current_cl->and_cl)
			current_cl = current_cl->and_cl;
		else
			current_cl = current_cl->semicolon_cl;
	}
	return (0);
}

int	parse_n_execute(char *str)
{
	t_list	*token_list;
	t_cl	*cl_root;
	int		ret;

	if (!str)
		return (0);
	token_list = split_to_tokens(str);
	if (!token_list)
		return (-1);
	if (check_syntax(token_list))
	{
		free_token_list(token_list);
		return (-1);
	}
	cl_root = parse_command_line(token_list);
	if (!cl_root)
	{
		free_token_list(token_list);
		return (-1);
	}
	ret = execute_syntax_tree(cl_root);
	free_token_list(token_list);
	free_syntax_tree(cl_root);
	return (ret);
}
