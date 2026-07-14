/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 16:00:47 by synoshah          #+#    #+#             */
/*   Updated: 2026/06/18 16:01:59 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **lst)
{
	t_token	*curr;
	t_token	*next_node;

	if (lst == NULL || *lst == NULL)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		next_node = curr->next;
		if (curr->value != NULL)
			free(curr->value);
		free(curr);
		curr = next_node;
	}
	*lst = NULL;
}
