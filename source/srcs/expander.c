/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:12:50 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/02 14:12:50 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_str(char *orig, int i, int len, char *env_val)
{
	char	*prefix;
	char	*suffix;
	char	*temp;
	char	*final;

	prefix = ft_substr(orig, 0, i);
	suffix = ft_strdup(orig + i + 1 + len);
	temp = ft_strjoin(prefix, env_val);
	final = ft_strjoin(temp, suffix);
	free(prefix);
	free(suffix);
	free(temp);
	free(orig);
	return (final);
}

static char	*get_val_and_len(char *str, int i, t_shell *shell, int *len)
{
	char	*key;
	char	*env_val;

	if (str[i + 1] == '?')
	{
		*len = 1;
		return (ft_itoa(shell->exit_status));
	}
	*len = 1;
	if (!str[i + 1] || str[i + 1] == ' ' || str[i + 1] == '\"')
	{
		*len = 0;
		return (ft_strdup("$"));
	}
	while (ft_isalnum(str[i + *len]) || str[i + *len] == '_')
		(*len)++;
	(*len)--;
	key = ft_substr(str, i + 1, *len);
	env_val = get_env_val(shell->env, key);
	free(key);
	if (!env_val)
		return (ft_strdup(""));
	return (ft_strdup(env_val));
}

static void	process_token_string(t_token *curr, t_shell *shell)
{
	int		i;
	int		in_s;
	int		in_d;
	int		len;
	char	*env_val;

	i = 0;
	in_s = 0;
	in_d = 0;
	while (curr->value[i] != '\0')
	{
		if (curr->value[i] == '\"' && !in_s)
			in_d = !in_d;
		else if (curr->value[i] == '\'' && !in_d)
			in_s = !in_s;
		else if (curr->value[i] == '$' && !in_s)
		{
			env_val = get_val_and_len(curr->value, i, shell, &len);
			curr->value = replace_str(curr->value, i, len, env_val);
			i = i + ft_strlen(env_val) - 1;
			free(env_val);
		}
		i++;
	}
}

void	expander(t_token *token_list, t_shell *shell)
{
	t_token	*curr;

	curr = token_list;
	while (curr != NULL)
	{
		if (curr->type == TOKEN_WORD)
			process_token_string(curr, shell);
		curr = curr->next;
	}
}
