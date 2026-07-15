/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:09:33 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/15 14:23:16 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(t_cmd *cmd, t_shell *shell)
{
	t_env	*curr;

	if (cmd->args[1])
	{
		ft_putendl_fd(S_ERR_ENV_ARGS, 2);
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	curr = shell->env;
	while (curr)
	{
		if (curr->value)
		{
			ft_putstr(curr->key);
			ft_putchar('=');
			ft_putendl(curr->value);
		}
		curr = curr->next;
	}
	shell->exit_status = EXIT_SUCCESS;
}
