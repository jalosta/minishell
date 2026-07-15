/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:39:38 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/15 14:39:38 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define S_NULL "(null)"

int	ft_putstr(const char *s)
{
	int	count;
	int	e_check;

	count = 0;
	if (!s)
		return (ft_putstr(S_NULL));
	while (*s)
	{
		e_check = ft_putchar(*s);
		if (e_check == WRITE_FAIL)
			return (WRITE_FAIL);
		count += e_check;
		s++;
	}
	return (count);
}
