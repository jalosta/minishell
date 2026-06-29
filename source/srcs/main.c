/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 20:23:52 by synoshah          #+#    #+#             */
/*   Updated: 2026/06/29 21:49:00 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_sig = 0;

static void	sigint_handler(int sig)
{
	g_sig = sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	shell_loop(t_shell *shell)
{
	char	*input;
	t_cmd	*cmds;
	t_token	*token_list;

	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		if (*input != '\0')
		{
			add_history(input);
			token_list = NULL;
			cmds = NULL;
			lexer(input, &token_list);
			expander(token_list, shell);
			trim_quotes(token_list);
			cmds = parse_input(token_list, shell);
			if (cmds != NULL)
			{
				execute_cmds(cmds, shell);
				free_cmds(cmds);
			}
			free_tokens(&token_list);
		}
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
	init_signals();
	shell_loop(&shell);
	free_env(shell.env);
	ft_putendl_fd("", STDOUT_FILENO);
	return (0);
}
