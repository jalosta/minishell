/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:09:21 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/15 14:24:45 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_identifier(char *s)
{
	int	i;

	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (false);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	add_or_update_env(t_shell *shell, char *arg)
{
	char	*key;
	char	*value;
	char	*equal_sign;
	t_env	*curr;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		key = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	curr = shell->env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (value)
			{
				free(curr->value);
				curr->value = value;
			}
			free(key);
			return ;
		}
		curr = curr->next;
	}
	curr = ft_malloc(sizeof(t_env));
	curr->key = key;
	curr->value = value;
	curr->next = shell->env;
	shell->env = curr;
}

static void	print_export(t_shell *shell)
{
	t_env	*curr;

	curr = shell->env;
	while (curr)
	{
		ft_putstr(S_EXP_FORMAT);
		ft_putstr(curr->key);
		if (curr->value)
		{
			ft_putstr("=\"");
			ft_putstr(curr->value);
			ft_putstr("\"");
		}
		ft_putstr("\n");
		curr = curr->next;
	}
}

void	exec_export(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (!cmd->args[1])
	{
		print_export(shell);
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_identifier(cmd->args[i]))
		{
			ft_putstr_fd(S_ERR_EXPORT, 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putendl_fd(S_ERR_EXPORT_ID, 2);
			shell->exit_status = 1;
		}
		else
			add_or_update_env(shell, cmd->args[i]);
		i++;
	}
}
