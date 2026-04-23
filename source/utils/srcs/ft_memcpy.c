/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 11:50:53 by codespace         #+#    #+#             */
/*   Updated: 2026/01/05 12:36:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    char *d;
    const char *s;

    if (dest == src && n == 0)
        return (dest);
    d = (char *)dest;
    s = (const char *)src;
    while (n--)
        *d++ = *s++;
    return (dest);
}