#include "minishell.h"

#define K_HOME	"HOME"
#define S_ERR_HOME "minishell: cd: HOME not set"
#define S_ERR_ARGS "minishell: cd: too many arguments"

static char	*get_cd_path(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (!cmd->args[1])
	{
		path = get_env_val(shell->env, K_HOME);
		if (!path)
		{
			ft_putendl_fd(S_ERR_HOME, 2);
			shell->exit_status = EXIT_FAILURE;
			return (NULL);
		}
		return (path);
	}
	if (cmd->args[2])
	{
		ft_putendl_fd(S_ERR_ARGS, 2);
		shell->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	return (cmd->args[1]);
}

#define S_ERR_CD	"minishell: cd: "

void	exec_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	path = get_cd_path(cmd, shell);
	if (!path)
		return ;
	if (chdir(path) != 0)
	{
		ft_putstr_fd(S_ERR_CD, 2);
		perror(path);
		shell->exit_status = EXIT_FAILURE;
	}
	else
		shell->exit_status = EXIT_SUCCESS;
}
