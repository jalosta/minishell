/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 20:23:52 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/12 00:56:22 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

void	sigint_handler(int sig)
{
	g_sig = sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	check_syntax(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == TOKEN_PIPE)
		{
			if (curr == tokens || !curr->next || curr->next->type == TOKEN_PIPE)
			{
				ft_putendl_fd("minishell: syntax error", 2);
				return (1);
			}
		}
		else if (curr->type != TOKEN_WORD)
		{
			if (!curr->next || curr->next->type != TOKEN_WORD)
			{
				ft_putendl_fd("minishell: syntax error", 2);
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

static void	process_input(char *input, t_shell *shell)
{
	t_token	*token_list;
	t_cmd	*cmds;

	if (g_sig == SIGINT)
		g_sig = 0;
	add_history(input);
	token_list = NULL;
	cmds = NULL;
	if (lexer(input, &token_list) != 0)
		return ;
	if (check_syntax(token_list))
	{
		shell->exit_status = 258;
		free_tokens(&token_list);
		return ;
	}
	expander(token_list, shell);
	trim_quotes(token_list);
	cmds = parse_input(token_list, shell);
	free_tokens(&token_list);
	execute_cmds(cmds, shell);
	free_cmds(cmds);
}

static void	shell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (*input != '\0')
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
	return (0);
}
