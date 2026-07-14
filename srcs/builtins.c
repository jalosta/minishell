#include "minishell.h"

#define CD	"cd"
#define ENV	"env"
#define PWD	"pwd"
#define EXIT	"exit"
#define EXPORT	"export"
#define UNSET	"unset"
#define ECHO	"echo"

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*s;

	s = cmd->args[0];
	if (!ft_strcmp(s, CD))
		exec_cd(cmd, shell);
	else if (!ft_strcmp(s, ENV))
		exec_env(cmd, shell);
	else if (!ft_strcmp(s, PWD))
		exec_pwd(cmd, shell);
	else if (!ft_strcmp(s, EXIT))
		exec_exit(cmd, shell);
	else if (!ft_strcmp(s, EXPORT))
		exec_export(cmd, shell);
	else if (!ft_strcmp(s, UNSET))
		exec_unset(cmd, shell);
	else if (!ft_strcmp(s, ECHO))
		exec_echo(cmd, shell);
	else
		return (EXIT_FAILURE);
	return (shell->exit_status);
}
