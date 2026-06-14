#include "minishell.h"

void free_tokens(t_token **lst)
{
    t_token *curr;
    t_token *next_node;

    if (lst == NULL || *lst == NULL)
        return;

    curr = *lst;
    while (curr != NULL)
    {
        next_node = curr->next;
        if (curr->value != NULL)
            free(curr->value);
        free(curr);
        curr = next_node;
    }
    *lst = NULL;
}