/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalosta- <jalosta-@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 16:03:30 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/14 16:46:49 by jalosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	extract_word(char *input, int start, int i, t_token **lst)
{
	char	*word;
	t_token	*node;

	if (i > start)
	{
		word = ft_substr(input, start, i - start);
		node = new_token(word, get_token_type(word));
		add_token_back(lst, node);
	}
}

static void	handle_metachar(char *input, int *i, t_token **lst)
{
	char	*word;
	t_token	*node;

	if (input[*i] == input[*i + 1] && input[*i] != '|')
	{
		word = ft_substr(input, *i, 2);
		(*i)++;
	}
	else
		word = ft_substr(input, *i, 1);
	node = new_token(word, get_token_type(word));
	add_token_back(lst, node);
}

static void	process_delim(char *in, int *i, int *start, t_token **lst)
{
	extract_word(in, *start, *i, lst);
	if (is_metachar(in[*i]))
		handle_metachar(in, i, lst);
	*start = *i + 1;
}

#define S_ERR_UNCLOSED_QUOTES "minishell error: unclosed quotes"

int	lexer(char *in, t_token **lst)
{
	int	i;
	int	st;
	int	single;
	int	doubleq;

	i = -1;
	st = 0;
	single = 0;
	doubleq = 0;
	while (in[++i])
	{
		if (in[i] == '\'' && !doubleq)
			single = !single;
		else if (in[i] == '\"' && !single)
			doubleq = !doubleq;
		else if ((in[i] == ' ' || is_metachar(in[i])) && !single && !doubleq)
			process_delim(in, &i, &st, lst);
	}
	if (single || doubleq)
	{
		ft_putendl_fd(S_ERR_UNCLOSED_QUOTES, 2);
		return (EXIT_FAILURE);
	}
	extract_word(in, st, i, lst);
	return (EXIT_SUCCESS);
}
