/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalosta- <jalosta-@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:04:01 by codespace         #+#    #+#             */
/*   Updated: 2026/05/17 15:27:29 by jalosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long	nbr;
	int		sign;

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
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = nbr * 10 + (*nptr - '0');
		if ((sign * nbr > INT_MAX) || (sign * nbr < INT_MIN))
			return (EXIT_FAILURE);
		nptr++;
	}
	return (sign * (int)nbr);
}
