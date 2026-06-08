#include "minishell.h"

int is_metachar(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (1);
    return (0);
}

int lexer(char *input)
{
    int in_single;
    int in_double;
    int i;
    int start;
    char *word;

    i = -1;
    in_double = 0;
    in_single = 0;
    start = 0;
    while (input[++i] != '\0')
    {
        if (input[i] == '\'' && !in_double)
            in_single = !in_single;
        else if (input[i] == '\"' && !in_single)
            in_double = !in_double;
        else if ((input[i] == ' ' || is_metachar(input[i]))
         && !in_single && !in_double)
        {
            if (i > start)
                word = ft_substr(input, start, i - start);
            if (is_metachar(input[i]))
            {
                if (input[i] == input[i + 1] && input[i] != '|')
                {
                    word = ft_substr(input, i, 2);
                    i++;
                }
                else
                    word = ft_substr(input, i, 1);
            }
            start = i + 1;
        }
    }
    if (in_single || in_double)
    {
        ft_putendl_fd("Minishell error: unclosed quote", 2);
        return (1);
    }
    if (i > start)
        word = ft_substr(input, start, i - start);
    return (0);
}

