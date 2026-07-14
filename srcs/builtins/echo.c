#include "minishell.h"

#define ECHO_OPT_N "-n"

void	exec_echo(t_cmd *cmd, t_shell *shell)
{
	int		i;
	bool	nl;

	i = 1;
	nl = TRUE;
	while (cmd->args[i] && !ft_strcmp(cmd->args[i], ECHO_OPT_N))
	{
		nl = FALSE;
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
