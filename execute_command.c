
#include "minishell.h"

static pid_t	launch_command(t_com *command, int fd_in, int fd_out)
{
	pid_t	fork_return;

	fd_in = ext_open(command->in, fd_in, 0, command->in_flag, command->out_flag);
	fd_out = ext_open(command->out, fd_out, 1, command->in_flag, command->out_flag);
	if ((fork_return = find_command(&command->command_path, command->args_array)) == -1)
		printf("%s: command not found\n", command->command_path);
	else if (!fork_return)
		run_builtin(command->args_array);
	else
	{
		if ((fork_return = fork()) == -1)
			perror("fork");
		else if (fork_return == 0)
		{
			//ext_pipe_close(pipe_in, 1);
			//ext_pipe_close(pipe_out, 0);
			execve(command->command_path, command->args_array, NULL);
			perror(command->command_path);
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
	pid_t	command_pid;

	fd_pipe_out = -1;
	fd_pipe_in = -1;
	while (current_job)
	{
		if (fd_pipe_out != -1)
		{
			fd_pipe_in = fd_pipe[0];
			dup2(fd_pipe_in, 0);
		}
		if (current_job->next_job)
		{
			fd_pipe_out = pipe(fd_pipe);
			fd_pipe_out = fd_pipe[1];
			dup2(fd_pipe_out, 1);
		}
		else
			dup2(fd_stdout, 1);
		command_pid = launch_command(current_job->com, fd_pipe_in, fd_pipe_out);
		current_job = current_job->next_job;
	}
	waitpid(command_pid, NULL, 0);
	return (0);
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

	token_list = split_to_tokens(str);
	if (!token_list)
		return (-1);
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
