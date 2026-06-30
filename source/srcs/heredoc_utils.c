#include "minishell.h"

static char	*safe_strjoin(char *s1, char *s2)
{
	char	*new_str;

	if (s2 == NULL)
		return (s1);
	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

static char	*safe_charjoin(char *s, char c)
{
	char	*new_str;
	int		len;

	len = ft_strlen(s);
	new_str = ft_malloc(sizeof(char) * (len + 2));
	ft_strlcpy(new_str, s, len + 1);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(s);
	return (new_str);
}

static char	*expand_var(char *line, int *i, t_shell *shell, char *res)
{
	char	*v_val;
	char	*v_name;
	int		start;

	(*i)++;
	if (line[*i] == '?')
	{
		v_val = ft_itoa(shell->exit_status);
		res = safe_strjoin(res, v_val);
		free(v_val);
		(*i)++;
	}
	else
	{
		start = *i;
		while (ft_isalnum(line[*i]) || line[*i] == '_')
			(*i)++;
		v_name = ft_substr(line, start, *i - start);
		v_val = get_env_val(shell->env, v_name);
		if (v_val != NULL)
			res = safe_strjoin(res, v_val);
		free(v_name);
	}
	return (res);
}

char	*expand_heredoc_line(char *line, t_shell *shell)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$' && line[i + 1] != '\0' && line[i + 1] != ' ')
			result = expand_var(line, &i, shell, result);
		else
		{
			result = safe_charjoin(result, line[i]);
			i++;
		}
	}
	free(line);
	return (result);
}
