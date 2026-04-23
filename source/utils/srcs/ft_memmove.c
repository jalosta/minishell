/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:04:32 by codespace         #+#    #+#             */
/*   Updated: 2026/01/05 13:01:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void *ft_memmove(void *dest, const void *src, size_t n)
{
    char *d;
    const char *s;
    
    if (dest == src && n == 0)
        return (dest);
    d = (char *)dest;
    s = (const char *)src;
    if (d > s)
    {
        while (n--)
            d[n] = s[n];
        return (dest);
    }
    else
        return (ft_memcpy(dest, src, n));
}