#include "minishell.h"

void expander(t_token *token_list, t_env *env_list)
{
    t_token *curr;
    
    curr = token_list;
    int i;
    int in_single;
    char *key;
    char *env_val;
    int len;
    char *prefix;
    char *suffix;
    char *temp;
    char *final;

    while (curr != NULL)
    {
        i = 0;
        in_single = 0;
        if (curr->type == TOKEN_WORD)
        {
            while (curr->value[i] != '\0')
            {
                if (curr->value[i] == '\'')
                    in_single = !in_single;
                else if (curr->value[i] == '$' && !in_single)
                {
                    len = 1;
                    while (ft_isalnum(curr->value[i + len]) || curr->value[i + len] == '_')
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
