#include "minishell.h"

int lexer(char *input)
{
    int in_single;
    int in_double;
    int i;
    int start;

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
    }
    if (in_single || in_double)
    {
        ft_putendl_fd("Minishell error: unclosed quote", 2);
        return (1);
    }
    return (0);
}

