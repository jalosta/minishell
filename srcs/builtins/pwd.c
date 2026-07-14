#include "minishell.h"

#define S_ERR_PWD_ARGS "minishell: pwd: too many arguments"
#define S_ERR_PWD "minishell: pwd: "

void	exec_pwd(t_cmd *cmd, t_shell *shell)
{
	char	*cwd;

	if (cmd->args[1])
	{
		ft_putendl_fd(S_ERR_PWD_ARGS, 2);
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putendl_fd(cwd, 1);
		free(cwd);
		shell->exit_status = EXIT_SUCCESS;
	}
	else
	{
		perror(S_ERR_PWD);
		shell->exit_status = EXIT_FAILURE;
	}
}
