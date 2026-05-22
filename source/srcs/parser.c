#include "minishell.h"

static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd));
	ft_bzero(cmd, sizeof(t_cmd));
	return (cmd);
}

t_cmd	*parse_input(char *input, t_shell *shell)
{
	t_cmd	*cmd;
	char	**tokens;

	(void)shell;
	if (*input == '\0')
		return (NULL);
	tokens = ft_split(input, ' ');
	if (tokens == NULL || tokens[0] == NULL)
	{
		free(tokens);
		return (NULL);
	}
	cmd = new_cmd();
	cmd->args = tokens;
	return (cmd);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd *tmp;
	int i;

	while (cmds != NULL)
	{
		tmp = cmds;
		cmds = cmds->next;
		if (tmp->args != NULL)
		{
			i = 0;
			while (tmp->args[i] != NULL)
				free(tmp->args[i++]);
			free(tmp->args);
		}
		free(tmp->in_file);
		free(tmp->out_file);
		free(tmp->heredoc_delim);
		free(tmp);
	}
}
