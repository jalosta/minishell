/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:09:27 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/15 14:24:39 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_putendl(cwd);
		free(cwd);
		shell->exit_status = EXIT_SUCCESS;
	}
	else
	{
		perror(S_ERR_PWD);
		shell->exit_status = EXIT_FAILURE;
	}
}
