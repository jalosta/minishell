/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:39:42 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/15 14:39:42 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	int		e_check;
	char	*nbr;

	nbr = ft_itoa(n);
	if (!nbr)
		return (0);
	e_check = ft_putstr(nbr);
	free(nbr);
	if (e_check == WRITE_FAIL)
		return (WRITE_FAIL);
	return (e_check);
}
