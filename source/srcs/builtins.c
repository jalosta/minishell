#include "minishell.h"

static void	exec_cd(t_cmd *cmd, t_shell *shell)
{
	if (cmd->args[1] == NULL)
		return ;
	if (chdir(cmd->args[1]) != 0)
	{
		perror("minishell: cd");
		shell->exit_status = EXIT_FAILURE;
	}
	else
		shell->exit_status = EXIT_SUCCESS;
}

static void	exec_env(t_shell *shell)
{
	t_env	*curr;

	curr = shell->env;
	while (curr != NULL)
	{
		if (curr->value != NULL)
		{
			ft_putstr_fd(curr->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(curr->value, STDOUT_FILENO);
		}
		curr = curr->next;
	}
	shell->exit_status = EXIT_SUCCESS;
}

static void	exec_pwd(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
		shell->exit_status = EXIT_SUCCESS;
	}
	else
	{
		perror("minishell: pwd");
		shell->exit_status = EXIT_FAILURE;
	}
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*name;

	name = cmd->args[0];
	if (ft_strncmp(name, "cd", 3) == EQUAL)
		exec_cd(cmd, shell);
	else if (ft_strncmp(name, "env", 4) == EQUAL)
		exec_env(shell);
	else if (ft_strncmp(name, "pwd", 4) == EQUAL)
		exec_pwd(shell);
	else if (ft_strncmp(name, "exit", 5) == EQUAL)
		exec_exit(cmd, shell);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
