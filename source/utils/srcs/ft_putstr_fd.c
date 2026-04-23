/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalosta- <jalosta-@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:33:00 by jalosta-          #+#    #+#             */
/*   Updated: 2026/04/23 10:50:23 by jalosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putstr_fd(const char *s, int fd)
{
	int	count;
	int	e_check;

	count = 0;
	if (s == NULL)
		return (ft_putstr_fd("(null)", fd));
	while (*s)
	{
		e_check = ft_putchar_fd(*s, fd);
		if (e_check == WRITE_FAIL)
			return (WRITE_FAIL);
		count += e_check;
		s++;
	}
	return (count);
}
