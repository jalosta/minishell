#include "minishell.h"

static char *safe_strjoin(char *s1, char *s2)
{
    char    *new_str;

    if (s2 == NULL)
        return (s1);
    new_str = ft_strjoin(s1, s2);
    free(s1);
    return (new_str);
}

static char *safe_charjoin(char *s, char c)
{
    char    *new_str;
    int     len;

    len = ft_strlen(s);
    new_str = ft_malloc(sizeof(char) * (len + 2));
    ft_strlcpy(new_str, s, len + 1);
    new_str[len] = c;
    new_str[len + 1] = '\0';
    free(s);
    return (new_str);
}

char    *expand_heredoc_line(char *line, t_shell *shell)
{
    char    *result;
    char    *var_name;
    char    *var_val;
    int     i;
    int     start;

    result = ft_strdup("");
    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '$' && line[i + 1] != '\0' && line[i + 1] != ' ')
        {
            i++;
            if (line[i] == '?')
            {
                var_val = ft_itoa(shell->exit_status);
                result = safe_strjoin(result, var_val);
                free(var_val);
                i++;
            }
            else
            {
                start = i;
                while (ft_isalnum(line[i]) || line[i] == '_')
                    i++;
                var_name = ft_substr(line, start, i - start);
                var_val = get_env_val(shell->env, var_name);
                if (var_val != NULL)
                    result = safe_strjoin(result, var_val);
                free(var_name);
            }
        }
        else
        {
            result = safe_charjoin(result, line[i]);
            i++;
        }
    }
    free(line);
    return (result);
}
