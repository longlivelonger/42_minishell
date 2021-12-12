#include	"minishell.h"

int	ext_close(int	fd)
{
	if (fd != -1)
		return (close(fd));
	else
		return (fd);
}

int	ext_pipe_close(int pipe[2], int	end_to_close)
{
	if (pipe[0] != -1)
		return (close(pipe[end_to_close]));
	else
		return (pipe[0]);
}

int	ext_open(char *file, int fd, int end_to_open)
{
	int	temp_fd;

	if (file)
	{
		temp_fd = fd;
		if (end_to_open == 0)
		{	
			fd = open(file, O_RDONLY);
			dup2(fd, 0);
			if (temp_fd != -1)
				close(temp_fd);
		}
		else
		{
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			dup2(fd, 1);
			if (temp_fd != -1)
				close(temp_fd);
		}
	}
	return (fd);
}
