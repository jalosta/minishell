/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalosta- <jalosta-@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:31:51 by jalosta-          #+#    #+#             */
/*   Updated: 2026/04/23 10:47:27 by jalosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	count_digit_places(int n)
{
	int	d;

	d = 1;
	while (n / 10)
	{
		n /= 10;
		d++;
	}
	return (d);
}

char	*ft_itoa(int n)
{
	int		places;
	char	*nbr;
	bool	last_place;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	places = count_digit_places(n);
	last_place = n < 0;
	places += last_place;
	nbr = malloc(places + 1);
	if (nbr == NULL)
		return (NULL);
	nbr[places] = '\0';
	if (n < 0)
	{
		n = -n;
		*nbr = '-';
	}
	while (places-- > last_place)
	{
		nbr[places] = n % 10 + '0';
		n /= 10;
	}
	return (nbr);
}
