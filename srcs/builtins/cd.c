/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:09:38 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/15 14:22:13 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	update_pwd_vars(t_shell *shell, char *old_path)
{
	char	*new_path;
	char	*env_str;

	if (old_path)
	{
		env_str = ft_strjoin("OLDPWD=", old_path);
		add_or_update_env(shell, env_str);
		free(env_str);
		free(old_path);
	}
	new_path = getcwd(NULL, 0);
	if (new_path)
	{
		env_str = ft_strjoin("PWD=", new_path);
		add_or_update_env(shell, env_str);
		free(env_str);
		free(new_path);
	}
}

void	exec_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	*old_path;

	path = get_cd_path(cmd, shell);
	if (!path)
		return ;
	old_path = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		ft_putstr_fd(S_ERR_CD, 2);
		perror(path);
		free(old_path);
		shell->exit_status = EXIT_FAILURE;
	}
	else
	{
		update_pwd_vars(shell, old_path);
		shell->exit_status = EXIT_SUCCESS;
	}
}
