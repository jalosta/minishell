#include "minishell.h"

#define S_EXP_FORMAT "declare -x "
#define S_ERR_EXPORT "minishell: export: `"
#define S_ERR_EXPORT_ID "': not a valid identifier"

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

static void	add_new_node(t_shell *shell, char *key, char *eq)
{
	t_env	*new_node;
	t_env	*curr;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = key;
	new_node->value = NULL;
	if (eq)
		new_node->value = ft_strdup(eq + 1);
	new_node->next = NULL;
	if (!shell->env)
	{
		shell->env = new_node;
		return ;
	}
	curr = shell->env;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
}

void	add_or_update_env(t_shell *shell, char *arg)
{
	char	*eq;
	char	*key;
	t_env	*curr;

	eq = ft_strchr(arg, '=');
	key = ft_strdup(arg);
	if (eq)
		key[eq - arg] = '\0';
	curr = shell->env;
	while (curr && ft_strcmp(curr->key, key) != 0)
		curr = curr->next;
	if (curr)
	{
		free(key);
		if (eq)
		{
			free(curr->value);
			curr->value = ft_strdup(eq + 1);
		}
		return ;
	}
	add_new_node(shell, key, eq);
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
