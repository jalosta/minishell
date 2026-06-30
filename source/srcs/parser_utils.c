#include "minishell.h"

int	count_args(t_token *start)
{
	t_token	*curr;
	int		count;

	count = 0;
	curr = start;
	while (curr != NULL && curr->type != TOKEN_PIPE)
	{
		if (curr->type == TOKEN_WORD)
			count++;
		curr = curr->next;
	}
	return (count);
}

static void	handle_out(t_cmd *cmd, t_token **curr, int is_app)
{
	int	fd;

	*curr = (*curr)->next;
	if (*curr && (*curr)->type == TOKEN_WORD)
	{
		if (cmd->out_file)
			free(cmd->out_file);
		cmd->out_file = ft_strdup((*curr)->value);
		cmd->append = is_app;
		if (is_app)
			fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd != -1)
			close(fd);
	}
}

void	handle_redirections(t_cmd *cmd, t_token **curr)
{
	if ((*curr)->type == TOKEN_REDIR_OUT || (*curr)->type == TOKEN_APPEND)
		handle_out(cmd, curr, (*curr)->type == TOKEN_APPEND);
	else if ((*curr)->type == TOKEN_REDIR_IN)
	{
		*curr = (*curr)->next;
		if (*curr && (*curr)->type == TOKEN_WORD)
		{
			if (cmd->in_file)
				free(cmd->in_file);
			cmd->in_file = ft_strdup((*curr)->value);
		}
	}
}
