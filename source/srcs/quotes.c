/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:12:29 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/02 14:12:30 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strip_string_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		in_single;
	int		in_double;

	new_str = ft_malloc(ft_strlen(str) + 1);
	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '\"' && !in_single)
			in_double = !in_double;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	trim_quotes(t_token *token_list)
{
	t_token	*curr;
	char	*temp;

	curr = token_list;
	while (curr != NULL)
	{
		if (curr->type == TOKEN_WORD)
		{
			temp = strip_string_quotes(curr->value);
			free(curr->value);
			curr->value = temp;
		}
		curr = curr->next;
	}
}
