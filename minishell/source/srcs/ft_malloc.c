#include "minishell.h"

void *ft_malloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (ptr == NULL)
    {
        perror("minishell: malloc");
        exit(EXIT_FAILURE);
    }
    return (ptr);
}