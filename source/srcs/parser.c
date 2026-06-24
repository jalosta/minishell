#include "minishell.h"

static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd));
	ft_bzero(cmd, sizeof(t_cmd));
	return (cmd);
}

static int	count_args(t_token *start_token)
{
	t_token	*curr;
	int		count;

	count = 0;
	curr = start_token;
	while (curr != NULL && curr->type != TOKEN_PIPE)
	{
		if (curr->type == TOKEN_WORD)
			count++;
		curr = curr->next;
	}
	return (count);
}

static void	handle_redirections(t_cmd *cmd, t_token **curr_ptr)
{
	if ((*curr_ptr)->type == TOKEN_REDIR_OUT)
	{
		*curr_ptr = (*curr_ptr)->next;
		if (*curr_ptr != NULL && (*curr_ptr)->type == TOKEN_WORD)
		{
			cmd->out_file = ft_strdup((*curr_ptr)->value);
			cmd->append = 0;
		}
	}
	else if ((*curr_ptr)->type == TOKEN_APPEND)
	{
		*curr_ptr = (*curr_ptr)->next;
		if (*curr_ptr != NULL && (*curr_ptr)->type == TOKEN_WORD)
		{
			cmd->out_file = ft_strdup((*curr_ptr)->value);
			cmd->append = 1;
		}
	}
	else if ((*curr_ptr)->type == TOKEN_REDIR_IN)
	{
		*curr_ptr = (*curr_ptr)->next;
		if (*curr_ptr != NULL && (*curr_ptr)->type == TOKEN_WORD)
			cmd->in_file = ft_strdup((*curr_ptr)->value);
	}
}

static void handle_heredoc(t_cmd *cmd, t_token **curr_ptr, t_shell *shell)
{
    char    *delim;
    char    *line;
    int     fd;
    int     expand_vars;

    *curr_ptr = (*curr_ptr)->next;
    if (*curr_ptr != NULL && (*curr_ptr)->type == TOKEN_WORD)
    {
        delim = (*curr_ptr)->value;
        expand_vars = 1;
        if (delim[0] == '\'' || delim[0] == '\"')
        {
            expand_vars = 0;
            ft_memmove(delim, delim + 1, ft_strlen(delim));
            delim[ft_strlen(delim) - 1] = '\0';
        }
        fd = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("minishell: heredoc");
            return ;
        }
        while (1)
        {
            line = readline("> ");
            if (line == NULL || ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
            {
                free(line);
                break ;
            }
            if (expand_vars == 1)
                line = expand_heredoc_line(line, shell);
                
            write(fd, line, ft_strlen(line));
            write(fd, "\n", 1);
            free(line);
        }
        close(fd);
        cmd->in_file = ft_strdup(".heredoc.tmp");
    }
}

t_cmd	*parse_input(t_token *token_list, t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*new_node;
	t_token	*curr;
	int		i;
	int		args_count;

	head = NULL;
	tail = NULL;
	(void)shell;
	if (token_list == NULL)
		return (NULL);

	curr = token_list;
	while (curr != NULL)
	{
		i = 0;
		new_node = new_cmd();
		args_count = count_args(curr);
		new_node->args = ft_malloc(sizeof(char *) * (args_count + 1));
		while (curr != NULL && curr->type != TOKEN_PIPE)
		{
			if (curr->type == TOKEN_WORD)
			{
				new_node->args[i] = ft_strdup(curr->value);
				i++;
			}
			else if (curr->type == TOKEN_REDIR_OUT
				|| curr->type == TOKEN_APPEND || curr->type == TOKEN_REDIR_IN)
				handle_redirections(new_node, &curr);
			else if (curr->type == TOKEN_HEREDOC)
				handle_heredoc(new_node, &curr, shell);
			if (curr != NULL)
				curr = curr->next;
		}
		new_node->args[i] = NULL;
		if (head == NULL)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		if (curr != NULL && curr->type == TOKEN_PIPE)
			curr = curr->next;
	}
	return (head);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	while (cmds != NULL)
	{
		tmp = cmds;
		cmds = cmds->next;
		if (tmp->args != NULL)
		{
			i = 0;
			while (tmp->args[i] != NULL)
				free(tmp->args[i++]);
			free(tmp->args);
		}
		free(tmp->in_file);
		free(tmp->out_file);
		free(tmp->heredoc_delim);
		free(tmp);
	}
}
