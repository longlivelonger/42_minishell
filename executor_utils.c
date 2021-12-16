#include	"minishell.h"

int	get_env_key(char *str)
{
	int	count;
	count = 0;
	while (*(str + count) && *(str + count) != '=')
		count++;
	return (count);
}

char	*find_env_value(char *key, int key_len, char **env, int *env_value_len)
{
	int	env_key_len;

	while (env)
	{
		env_key_len = get_env_key(*env);
		if (env_key_len == key_len)
		{
			if (!ft_strncmp(key, *env, key_len))
			{
				*env_value_len = 0;
				while (*(*env + env_key_len + *env_value_len + 1))
					(*env_value_len)++;
				return (*env);
			}
		}
		env++;
	}
	return (NULL);
}

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

int	ext_open(char *file, int fd, int end_to_open, int in_flag, int out_flag)
{
	int	temp_fd;

	if (file)
	{
		temp_fd = fd;
		if (end_to_open == 0)
		{	
			(void) in_flag;
			fd = open(file, O_RDONLY);
			dup2(fd, 0);
			if (temp_fd != -1)
				close(temp_fd);
		}
		else
		{
			fd = open(file, O_WRONLY | O_CREAT | out_flag, S_IRUSR | S_IWUSR);
			dup2(fd, 1);
			if (temp_fd != -1)
				close(temp_fd);
		}
	}
	return (fd);
}
