#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exec_exit(t_cmd *cmd, t_shell *shell)
{
	int	code;

	code = shell->exit_status;
	ft_putendl_fd("exit", 2);
	if (cmd->args[1] && !is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		code = 2;
	}
	else if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("minishell: too many arguments", 2);
		shell->exit_status = 1;
		return ;
	}
	else if (cmd->args[1])
		code = ft_atoi(cmd->args[1]);
	free_cmds(cmd);
	free_env(shell->env);
	exit(code);
}
