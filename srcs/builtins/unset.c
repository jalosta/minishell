#include "minishell.h"

static void	remove_env_var(t_shell *shell, char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = shell->env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key))
		{
			if (prev)
				prev->next = curr->next;
			else
				shell->env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
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
		remove_env_var(shell, cmd->args[i++]);
	shell->exit_status = EXIT_SUCCESS;
}
