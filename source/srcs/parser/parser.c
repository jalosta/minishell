/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:12:20 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/02 14:12:21 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd));
	ft_bzero(cmd, sizeof(t_cmd));
	return (cmd);
}

static void	populate_cmd(t_cmd *cmd, t_token **curr, t_shell *shell)
{
	int	i;

	i = 0;
	while (*curr != NULL && (*curr)->type != TOKEN_PIPE)
	{
		if ((*curr)->type == TOKEN_WORD)
			cmd->args[i++] = ft_strdup((*curr)->value);
		else if ((*curr)->type == TOKEN_REDIR_OUT
			|| (*curr)->type == TOKEN_APPEND
			|| (*curr)->type == TOKEN_REDIR_IN)
			handle_redirections(cmd, curr);
		else if ((*curr)->type == TOKEN_HEREDOC)
			handle_heredoc(cmd, curr, shell);
		if (*curr != NULL)
			*curr = (*curr)->next;
	}
	cmd->args[i] = NULL;
	if (*curr != NULL && (*curr)->type == TOKEN_PIPE)
		*curr = (*curr)->next;
}

t_cmd	*parse_input(t_token *token_list, t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*new_node;
	t_token	*curr;

	head = NULL;
	tail = NULL;
	curr = token_list;
	while (curr != NULL)
	{
		new_node = new_cmd();
		new_node->args = ft_malloc(sizeof(char *) * (count_args(curr) + 1));
		populate_cmd(new_node, &curr, shell);
		if (head == NULL)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
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
