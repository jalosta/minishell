#include "minishell.h"

static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd));
	ft_bzero(cmd, sizeof(t_cmd));
	return (cmd);
}

static int count_args(t_token *start_token)
{
    t_token *curr;
    int     count;

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

static void handle_redirections(t_cmd *cmd, t_token **curr_ptr)
{
    t_token *curr;

    curr = *curr_ptr;
    if (curr->type == TOKEN_REDIR_OUT)
    {
        curr = curr->next;
        if (curr != NULL && curr->type == TOKEN_WORD)
        {
            cmd->out_file = ft_strdup(curr->value);
            cmd->append = 0;
        }
    }
    else if (curr->type == TOKEN_APPEND)
    {
        curr = curr->next;
        if (curr != NULL && curr->type == TOKEN_WORD)
        {
            cmd->out_file = ft_strdup(curr->value);
            cmd->append = 1;
        }
    }
    else if (curr->type == TOKEN_REDIR_IN)
    {
        curr = curr->next;
        if (curr != NULL && curr->type == TOKEN_WORD)
            cmd->in_file = ft_strdup(curr->value);
    }
    *curr_ptr = curr;
}

t_cmd *parse_input(t_token *token_list, t_shell *shell)
{
    t_cmd   *head = NULL;
    t_cmd   *tail = NULL;
    t_cmd   *new_node;
    t_token *curr;
    int     i;
    int     args_count;

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
            else if (curr->type == TOKEN_REDIR_OUT ||
                 curr->type == TOKEN_APPEND || curr->type == TOKEN_REDIR_IN)
                handle_redirections(new_node, &curr);
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
	t_cmd *tmp;
	int i;

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
