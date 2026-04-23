/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:26:18 by codespace         #+#    #+#             */
/*   Updated: 2026/01/11 15:10:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char *ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!*little)
		return ((char *)big);
	while (len-- && *big)
	{
		i = 0;
		while (i < len && big[i] == little[i] && little[i])
			i++;
		if (!little[i])
			return ((char *)big);
		big++;
	}
	return (NULL);
}