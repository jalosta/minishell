/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalosta- <jalosta-@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:04:01 by jalosta-         #+#    #+#             */
/*   Updated: 2026/05/17 15:27:29 by jalosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_sign(char c)
{
	if (c == '-')
		return (NEGATIVE);
	return (POSITIVE);
}

static int	char_to_digit(int c)
{
	return (c - '0');
}

int	ft_atoi(const char *nptr)
{
	int		sgn;
	long	nbr;

	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		sgn = get_sign(*nptr);
		nptr++;
	}
	nbr = 0;
	while (ft_isdigit(*nptr))
	{
		nbr = nbr * 10 + char_to_digit(*nptr);
		if (sgn * nbr > INT_MAX || sgn * nbr < INT_MIN)
			return (EXIT_FAILURE);
		nptr++;
	}
	return (sgn * nbr);
}
