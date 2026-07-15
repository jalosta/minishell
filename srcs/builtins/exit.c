#include "minishell.h"

static bool	is_numeric(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	if (!*s)
		return (false);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

#define K_EXIT "exit"
#define S_ERR_EXIT "minishell: exit: "
#define S_ERR_EXIT_NUMERIC ": numeric argument required"
#define EXIT_NUM_ARGS 255
#define S_ERR_EXIT_ARGS "minishell: exit: too many arguments"

void	exec_exit(t_cmd *cmd, t_shell *shell)
{
	int	code;

	code = shell->exit_status;
	ft_putendl_fd(K_EXIT, 2);
	if (cmd->args[1] && !is_numeric(cmd->args[1]))
	{
		ft_putstr_fd(S_ERR_EXIT, 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putendl_fd(S_ERR_EXIT_NUMERIC, 2);
		code = EXIT_NUM_ARGS;
	}
	else if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd(S_ERR_EXIT_ARGS, 2);
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	else if (cmd->args[1])
		code = ft_atoi(cmd->args[1]);
	free_cmds(cmd);
	free_env(shell->env);
	exit(code);
}
