#include "minishell.h"

int is_metachar(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (1);
    return (0);
}

t_token_type get_token_type(char *word)
{   
    if (ft_strcmp(word, "|") == 0)
        return (TOKEN_PIPE);
    if (ft_strcmp(word, "<") == 0)
        return (TOKEN_REDIR_IN);
    if (ft_strcmp(word, ">") == 0)
        return (TOKEN_REDIR_OUT);
    if (ft_strcmp(word, "<<") == 0)
        return (TOKEN_HEREDOC);
    if (ft_strcmp(word, ">>") == 0)
        return (TOKEN_APPEND);
    return (TOKEN_WORD); 
}

t_token *new_token(char *word, t_token_type type)
{
    t_token *node;

    node = ft_malloc(sizeof(t_token));
    node->value = word;
    node->type = type;
    node->next = NULL;
    return (node);
}

void add_token_back(t_token **lst, t_token *new_node)
{
    t_token *curr;

    if (*lst == NULL)
    {
        *lst = new_node;
        return ;
    }
    curr = *lst;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = new_node;
}

int lexer(char *input, t_token **token_list)
{
    int in_single;
    int in_double;
    int i;
    int start;
    char *word;
    t_token *new_node;

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
            {
                word = ft_substr(input, start, i - start);
                new_node = new_token(word, get_token_type(word));
                add_token_back(token_list, new_node);
            }
            if (is_metachar(input[i]))
            {
                if (input[i] == input[i + 1] && input[i] != '|')
                {
                    word = ft_substr(input, i, 2);
                    i++;
                }
                else
                    word = ft_substr(input, i, 1);
                new_node = new_token(word, get_token_type(word));
                add_token_back(token_list, new_node);
            }
            start = i + 1;
        }
    }
    if (in_single || in_double)
    {
        ft_putendl_fd("\n", 2);
        return (1);
    }
    if (i > start)
    {
        word = ft_substr(input, start, i - start);
        new_node = new_token(word, get_token_type(word));
        add_token_back(token_list, new_node);
    }
    return (0);
}

