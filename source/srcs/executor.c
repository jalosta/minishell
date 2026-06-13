#include "minishell.h"

static char	*find_path(char *cmd, t_env *env)
{
	char	*paths;
	char	**split;
	char	*full;
	char	*temp;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = get_env_val(env, "PATH");
	if (paths == NULL)
		return (NULL);
	split = ft_split(paths, ':');
	i = 0;
	while (split != NULL && split[i] != NULL)
	{
		temp = ft_strjoin(split[i], "/");
		full = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full, X_OK) == 0)
		{
			while (split[i] != NULL)
				free(split[i++]);
			free(split);
			return (full);
		}
		free(split[i++]);
		free(full);
	}
	if (split)
		free(split);
	return (NULL);
}

static void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

static char	**env_list_to_array(t_env *env)
{
	int		count;
	t_env	*curr;
	char	**arr;
	char	*temp;

	count = 0;
	curr = env;
	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}
	arr = ft_malloc(sizeof(char *) * (count + 1));
	curr = env;
	count = 0;
	while (curr != NULL)
	{
		if (curr->value != NULL)
		{
			temp = ft_strjoin(curr->key, "=");
			arr[count] = ft_strjoin(temp, curr->value);
			free(temp);
		}
		else
			arr[count] = ft_strdup(curr->key);
		count++;
		curr = curr->next;
	}
	arr[count] = NULL;
	return (arr);
}

void	execute_cmds(t_cmd *cmds, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**env_arr;

	if (cmds->args == NULL || cmds->args[0] == NULL)
		return ;
	if (exec_builtin(cmds, shell) == EXIT_SUCCESS)
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		path = find_path(cmds->args[0], shell->env);
		if (path == NULL)
		{
			ft_putendl_fd("minishell: command not found", STDERR_FILENO);
			exit(EXIT_CMD_NOT_FOUND);
		}
		env_arr = env_list_to_array(shell->env);
		execve(path, cmds->args, env_arr);
		free_array(env_arr);
		perror("execve");
		exit(EXIT_CMD_CANNOT_EXECUTE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}
