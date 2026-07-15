/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:09:43 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/15 14:24:23 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

static void	remove_env_var(t_shell *shell, char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = shell->env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				shell->env = curr->next;
			free_env_node(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	exec_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		remove_env_var(shell, cmd->args[i]);
		i++;
	}
	shell->exit_status = EXIT_SUCCESS;
}
