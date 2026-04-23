/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:09:20 by codespace         #+#    #+#             */
/*   Updated: 2026/01/11 14:11:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t ft_strlcat(char *dst, const char *src, size_t size)
{
    size_t dst_len;
    size_t src_len;
    int i;
    
    dst_len = ft_strlen(dst);
    src_len = ft_strlen(src);
    if (dst_len >= size)
        return (dst_len + src_len);
    i = 0;
    while (i < size - dst_len - 1)
    {
        dst[i + dst_len] = src[i];
        i++;
    }
    dst[i + dst_len] = '\0';
    return (dst_len + src_len);
}