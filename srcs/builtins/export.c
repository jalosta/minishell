#include "minishell.h"

static bool	is_valid_identifier(char *s)
{
	if (!ft_isalpha(*s) && *s != '_')
		return (false);
	s++;
	while (*s && *s != '=')
	{
		if (!ft_isalnum(*s) && *s != '_')
			return (false);
		s++;
	}
	return (true);
}

static void	add_or_update_env(t_shell *shell, char *arg)
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

#define S_EXP_FORMAT "declare -x "

static void	print_export(t_shell *shell)
{
	t_env	*curr;

	curr = shell->env;
	while (curr)
	{
		ft_putstr_fd(S_EXP_FORMAT, 1);
		ft_putstr_fd(curr->key, 1);
		if (curr->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(curr->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		curr = curr->next;
	}
}

#define S_ERR_EXPORT "minishell: export: `"
#define S_ERR_EXPORT_ID "': not a valid identifier"

void	exec_export(t_cmd *cmd, t_shell *shell)
{
	int	i;

	shell->exit_status = EXIT_SUCCESS;
	if (!cmd->args[1])
		return (print_export(shell));
	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_identifier(cmd->args[i]))
		{
			ft_putstr_fd(S_ERR_EXPORT, 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putendl_fd(S_ERR_EXPORT_ID, 2);
			shell->exit_status = EXIT_FAILURE;
		}
		else
			add_or_update_env(shell, cmd->args[i]);
		i++;
	}
}
