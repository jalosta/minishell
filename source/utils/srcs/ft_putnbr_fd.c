/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalosta- <jalosta-@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:33:00 by jalosta-          #+#    #+#             */
/*   Updated: 2026/04/23 10:48:51 by jalosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int		e_check;
	char	*nbr;

	nbr = ft_itoa(n);
	if (nbr == NULL)
		return (0);
	e_check = ft_putstr_fd(nbr, fd);
	free(nbr);
	if (e_check == WRITE_FAIL)
		return (WRITE_FAIL);
	return (e_check);
}
