/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 11:17:14 by codespace         #+#    #+#             */
/*   Updated: 2026/01/04 11:49:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int ft_memcmp(const void *s1, const void *s2, size_t n)
{
    unsigned char *str1;
    unsigned char *str2;
    
    str1 = (unsigned char *)s1;
    str2 = (unsigned char *)s2;
    while (n--)
    {
        if (*str1 < *str2)
            return (NEGATIVE);
        else if (*str1 > *str2)
            return (1);
        str1++;
        str2++;
    }
    return (0);
}