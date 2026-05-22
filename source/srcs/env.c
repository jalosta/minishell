#include "minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*curr;
	char	*eq;

	head = NULL;
	while (envp != NULL && *envp != NULL)
	{
		curr = ft_malloc(sizeof(t_env));
		eq = ft_strchr(*envp, '=');
		if (eq != NULL)
		{
			curr->key = ft_substr(*envp, 0, eq - *envp);
			curr->value = ft_strdup(eq + 1);
		}
		else
		{
			curr->key = ft_strdup(*envp);
			curr->value = NULL;
		}
		curr->next = head;
		head = curr;
		envp++;
	}
	return (head);
}

char	*get_env_val(t_env *env, char *key)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == EQUAL)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	free_env(t_env *env)
{
	t_env *tmp;

	while (env != NULL)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
