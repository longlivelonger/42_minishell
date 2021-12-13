
#include "minishell.h"

void	free_token_list(t_list *tl)
{
	t_list	*temp;

	while (tl)
	{
		temp = tl;
		tl = tl->next;
		if (((t_token *)temp->content)->value)
			free(((t_token *)temp->content)->value);
		free((t_token *)temp->content);
		free(temp);
	}
}

static t_job	*free_job(t_job *job)
{
	t_job	*temp_job;

	//if (job->com->command_path)
	//	free(job->com->command_path);
	//if (job->com->in)
	//	free(job->com->in);
	//if (job->com->out)
	//	free(job->com->out);
	if (job->com->args_array)
		free(job->com->args_array);
	if (job->com)
		free(job->com);
	temp_job = job->next_job;
	free(job);
	return (temp_job);
}

void	free_syntax_tree(t_cl *cl)
{
	t_job	*temp_job;

	if (cl)
	{
		temp_job = cl->job;
		while (temp_job)
		{
			temp_job = free_job(temp_job);
		}
		if (cl->and_cl)
			free_syntax_tree(cl->and_cl);
		if (cl->semicolon_cl)
			free_syntax_tree(cl->semicolon_cl);
		free(cl);
	}
}
