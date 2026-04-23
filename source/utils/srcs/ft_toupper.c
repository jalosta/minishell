/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:56:06 by codespace         #+#    #+#             */
/*   Updated: 2026/01/11 14:56:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int ft_toupper(int c)
{
    if (c >= 'a' && c <= 'z')
        return (c - LOWER_TO_UPPER_CASE_DIFFERENCE);
}