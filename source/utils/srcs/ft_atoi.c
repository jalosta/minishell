/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:04:01 by codespace         #+#    #+#             */
/*   Updated: 2026/01/11 14:24:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int ft_atoi(const char *nptr)
{
    long nbr;
    int sign;

    while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n')
        nptr++;
    sign = POSITIVE;
    if (*nptr == '+' || *nptr == '-')
    {
        if (*nptr == '-')
            sign = NEGATIVE;
        nptr++;
    }
    nbr = 0;
    while (*nptr)
    {
        nbr = nbr * 10 + (*nptr - '0');
        if ((sign * nbr > INT_MAX) || (sign * nbr < INT_MIN))
            return EXIT_FAILURE;
        nptr++;
    }
    return (sign * (int)nbr);
}