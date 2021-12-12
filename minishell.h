#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "syntax_tree.h"
# include "tokens.h"
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>

void	run_command(char *command);

#endif
