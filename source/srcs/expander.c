/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 15:59:07 by synoshah          #+#    #+#             */
/*   Updated: 2026/06/18 15:59:07 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strip_string_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		in_single;
	int		in_double;

	new_str = ft_malloc(ft_strlen(str) + 1);
	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '\"' && !in_single)
			in_double = !in_double;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	trim_quotes(t_token *token_list)
{
	t_token	*curr;
	char	*temp;

	curr = token_list;
	while (curr != NULL)
	{
		if (curr->type == TOKEN_WORD)
		{
			temp = strip_string_quotes(curr->value);
			free(curr->value); 
			curr->value = temp; 
		}
		curr = curr->next;
	}
}

void	expander(t_token *token_list, t_env *env_list)
{
	t_token	*curr;
	int		i;
	int		in_single;
	int		in_double;
	char	*key;
	char	*env_val;
	int		len;
	char	*prefix;
	char	*suffix;
	char	*temp;
	char	*final;

	curr = token_list;
	while (curr != NULL)
	{
		i = 0;
		in_single = 0;
		in_double = 0;
		if (curr->type == TOKEN_WORD)
		{
			while (curr->value[i] != '\0')
			{
				if (curr->value[i] == '\"' && !in_single)
					in_double = !in_double;
				else if (curr->value[i] == '\'' && !in_double)
					in_single = !in_single;
				else if (curr->value[i] == '$' && !in_single)
				{
					len = 1;
					while (ft_isalnum(curr->value[i + len])
						|| curr->value[i + len] == '_')
						len++;
					len = len - 1;
					key = ft_substr(curr->value, i + 1, len);
					env_val = get_env_val(env_list, key);
					if (env_val == NULL)
						env_val = ft_strdup("");
					else
						env_val = ft_strdup(env_val);
					free(key);
					prefix = ft_substr(curr->value, 0, i);
					suffix = ft_strdup(curr->value + i + 1 + len);
					temp = ft_strjoin(prefix, env_val);
					final = ft_strjoin(temp, suffix);
					free(prefix);
					free(env_val);
					free(suffix);
					free(temp);
					free(curr->value);
					curr->value = final;
					i = i + ft_strlen(env_val) - 1;
				}
				i++;
			}
		}
		curr = curr->next;
	}
}
