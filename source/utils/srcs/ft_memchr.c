/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 11:03:29 by codespace         #+#    #+#             */
/*   Updated: 2026/01/04 11:19:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void *ft_memchr(const void *s, int c, size_t n)
{
    unsigned char *str;
    unsigned char uc;
    
    str = (unsigned char *)s;
    uc = (unsigned char)c;
    while (n--)
    {
        if (*str == uc)
            return ((void *)str);
        str++;
    }
    return (NULL);
}