#include "minishell.h"

#define S_ERR_ENV_ARGS "minishell: env: too many arguments"

void	exec_env(t_cmd *cmd, t_shell *shell)
{
	t_env	*curr;

	if (cmd->args[1])
	{
		ft_putendl_fd(S_ERR_ENV_ARGS, 2);
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	curr = shell->env;
	while (curr)
	{
		if (curr->value)
		{
			ft_putstr_fd(curr->key, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(curr->value, 1);
		}
		curr = curr->next;
	}
	shell->exit_status = EXIT_SUCCESS;
}
