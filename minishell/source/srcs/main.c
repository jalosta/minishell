#include "minishell.h"

typedef enum    e_token_type{
    T_WORD,
    T_PIPE,
    T_REDIR_IN,
    T_REDIR_OUT,
    T_REDIR_APPEND,
    T_HEREDOC
}   t_token_type;

typedef struct  s_token{
    char    *value;
    t_token_type    type;
    struct  s_token *next;
}   t_token;

size_t	count_words(char const *s)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		if (*s != ' ' && (*(s + 1) == ' ' || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

t_list	*line_tokenizer(char *line)
{
	size_t	word_count;
	t_list	*tokens;

	word_count = count_words(line);
	tokens = calloc(word_count, sizeof(t_list *));
	if (tokens == NULL)
		return (NULL);
	// tokens = ft_split(line, ' ');
	// if (tokens == NULL)
	// 	return (NULL);
	return (tokens);
}

void    shell_loop(void)
{
    char    *line;
	t_list	*tokens;

    line = readline("minishell$ ");
    while (line != NULL)
    {
        if (*line != '\0')
            add_history(line);
		tokens = line_tokenizer(line);
        if (tokens == NULL)
			free(line);
		ft_lstclear(&tokens, free);
        line = readline("minishell$ ");
    }
}

int main(void)
{
	shell_loop();
}