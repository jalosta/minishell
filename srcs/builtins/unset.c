#include "minishell.h"

#define S_ERR_UNSET "minishell: unset: `"
#define S_ERR_UNSET_ID "': not a valid identifier"

static bool	is_valid_identifier(char *s)
{
	int	i;

	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (false);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

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
	shell->exit_status = EXIT_SUCCESS;
	while (cmd->args[i])
	{
		if (!is_valid_identifier(cmd->args[i]))
		{
			ft_putstr_fd(S_ERR_UNSET, 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putendl_fd(S_ERR_UNSET_ID, 2);
			shell->exit_status = EXIT_FAILURE;
		}
		else
			remove_env_var(shell, cmd->args[i]);
		i++;
	}
}