/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 08:46:48 by codespace         #+#    #+#             */
/*   Updated: 2026/01/04 09:26:34 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void *ft_calloc(size_t nmemb, size_t size)
{
    void *ptr;

    if (!nmemb || !size)
        return (malloc(0));
    if (nmemb * size > INT_MAX)
        return (NULL);
    ptr = malloc(nmemb * sizeof(size));
    if (!ptr)
        return (NULL);
    ft_bzero(ptr, nmemb);
    return (ptr);
}