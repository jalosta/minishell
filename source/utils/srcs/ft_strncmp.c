/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalosta- <jalosta-@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:04:00 by jalosta-          #+#    #+#             */
/*   Updated: 2026/04/23 10:48:54 by jalosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- != 0)
	{
		if (*s1 < *s2)
			return (NEGATIVE);
		else if (*s1 > *s2)
			return (POSITIVE);
		s1++;
		s2++;
	}
	return (EQUAL);
}
