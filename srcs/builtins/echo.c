#include "minishell.h"

#define ECHO_OPT_N "-n"

static bool	is_n(char *arg)
{
	int	i;

	if (arg[0] != '-' || arg[1] != 'n')
		return (false);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	exec_echo(t_cmd *cmd, t_shell *shell)
{
	int		i;
	bool	nl;

	i = 1;
	nl = true;
	while (cmd->args[i] && is_n(cmd->args[i]))
	{
		nl = false;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 2);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', 2);
		i++;
	}
	if (nl)
		ft_putchar_fd('\n', 2);
	shell->exit_status = EXIT_SUCCESS;
}
