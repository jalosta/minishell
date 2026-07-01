#include "minishell.h"

int	is_metachar(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

t_token_type	get_token_type(char *word)
{
	if (ft_strncmp(word, "|", 2) == 0)
		return (TOKEN_PIPE);
	if (ft_strncmp(word, "<", 2) == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strncmp(word, ">", 2) == 0)
		return (TOKEN_REDIR_OUT);
	if (ft_strncmp(word, "<<", 3) == 0)
		return (TOKEN_HEREDOC);
	if (ft_strncmp(word, ">>", 3) == 0)
		return (TOKEN_APPEND);
	return (TOKEN_WORD);
}

t_token	*new_token(char *word, t_token_type type)
{
	t_token	*node;

	node = ft_malloc(sizeof(t_token));
	node->value = word;
	node->type = type;
	node->next = NULL;
	return (node);
}

void	add_token_back(t_token **lst, t_token *new_node)
{
	t_token	*curr;

	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	curr = *lst;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_node;
}
