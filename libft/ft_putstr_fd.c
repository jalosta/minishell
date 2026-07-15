/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:39:40 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/15 14:39:40 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(const char *s, int fd)
{
	int	count;
	int	e_check;

	count = 0;
	if (!s)
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
