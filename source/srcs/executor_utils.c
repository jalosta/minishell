#include "minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

static char	*check_valid_path(char **split, char *cmd)
{
	char	*exec_path;
	char	*dir;
	int		i;

	i = 0;
	while (split != NULL && split[i] != NULL)
	{
		dir = ft_strjoin(split[i], "/");
		exec_path = ft_strjoin(dir, cmd);
		free(dir);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		free(exec_path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_env *env)
{
	char	*paths;
	char	**split;
	char	*exec_path;

	paths = get_env_val(env, "PATH");
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (paths == NULL)
		return (NULL);
	split = ft_split(paths, ':');
	exec_path = check_valid_path(split, cmd);
	free_array(split);
	return (exec_path);
}

static int	get_env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env != NULL)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**env_list_to_array(t_env *env)
{
	int		size;
	char	**arr;
	char	*k_pre;

	size = get_env_size(env);
	arr = ft_malloc(sizeof(char *) * (size + 1));
	size = 0;
	while (env != NULL)
	{
		if (env->value != NULL)
		{
			k_pre = ft_strjoin(env->key, "=");
			arr[size++] = ft_strjoin(k_pre, env->value);
			free(k_pre);
		}
		else
			arr[size++] = ft_strdup(env->key);
		env = env->next;
	}
	arr[size] = NULL;
	return (arr);
}
