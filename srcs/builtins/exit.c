/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:09:30 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/15 14:09:30 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_numeric(char *s, long long *val)
{
	int					sign;
	unsigned long long	res;
	unsigned long long	limit;

	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!*s)
		return (false);
	res = 0;
	limit = 9223372036854775807ULL + (sign == -1);
	while (*s)
	{
		if (!ft_isdigit(*s) || res > (limit - (*s - '0')) / 10)
			return (false);
		res = res * 10 + (*s - '0');
		s++;
	}
	*val = (long long)(res * sign);
	return (true);
}

void	exec_exit(t_cmd *cmd, t_shell *shell)
{
	long long	code;

	code = shell->exit_status;
	ft_putendl_fd(K_EXIT, 2);
	if (cmd->args[1] && !is_numeric(cmd->args[1], &code))
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
	free_cmds(cmd);
	free_env(shell->env);
	exit(code);
}
