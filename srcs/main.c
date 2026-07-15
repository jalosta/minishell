/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:10:18 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/15 14:21:36 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

void	sigint_handler(int sig)
{
	g_sig = sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	check_syntax(t_token *head)
{
	t_token	*curr;

	curr = head;
	while (curr)
	{
		if (curr->type == TOKEN_PIPE)
		{
			if (curr == head || !curr->next || curr->next->type == TOKEN_PIPE)
			{
				ft_putendl_fd(S_ERR_SYNTAX, 2);
				return (EXIT_FAILURE);
			}
		}
		else if (curr->type != TOKEN_WORD)
		{
			if (!curr->next || curr->next->type != TOKEN_WORD)
			{
				ft_putendl_fd(S_ERR_SYNTAX, 2);
				return (EXIT_FAILURE);
			}
		}
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}

static void	process_input(char *input, t_shell *shell)
{
	t_token	*list;
	t_cmd	*cmds;

	if (g_sig == SIGINT)
		g_sig = 0;
	add_history(input);
	list = NULL;
	cmds = NULL;
	if (lexer(input, &list) != EXIT_SUCCESS)
		return ;
	if (check_syntax(list))
	{
		shell->exit_status = SYNTAX_ERROR;
		free_tokens(&list);
		return ;
	}
	expander(list, shell);
	trim_quotes(list);
	cmds = parse_input(list, shell);
	free_tokens(&list);
	execute_cmds(cmds, shell);
	free_cmds(cmds);
}

static void	shell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (*input)
			process_input(input, shell);
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env = init_env(envp);
	shell.exit_status = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	shell_loop(&shell);
	free_env(shell.env);
	return (EXIT_SUCCESS);
}
