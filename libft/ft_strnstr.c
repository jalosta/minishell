/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:39:07 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/15 14:39:07 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t len)
{
	size_t	i;

	if (*lit == '\0')
		return ((char *)big);
	while (len-- && *big != '\0')
	{
		i = 0;
		while (i < len && big[i] == lit[i] && lit[i] != '\0')
			i++;
		if (lit[i] == '\0')
			return ((char *)big);
		big++;
	}
	return (NULL);
}
