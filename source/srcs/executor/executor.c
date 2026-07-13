/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:27:15 by synoshah          #+#    #+#             */
/*   Updated: 2026/06/18 14:27:15 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "cd", 3) == 0 || ft_strncmp(cmd, "exit", 5) == 0
		|| ft_strncmp(cmd, "env", 4) == 0 || ft_strncmp(cmd, "pwd", 4) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0
		|| ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	return (0);
}

static void	execute_child(t_cmd *cmd, t_shell *sh, int fd[2], int p_fd)
{
	char	*path;
	char	**env_a;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	route_child_io(cmd, fd, p_fd);
	route_file_redirections(cmd, sh);
	if (!cmd->args || !cmd->args[0])
		exit(EXIT_SUCCESS);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, sh));
	path = find_path(cmd->args[0], sh->env);
	if (!path)
		ft_putstr_fd("minishell: command not found\n", 2);
	else
	{
		env_a = env_list_to_array(sh->env);
		execve(path, cmd->args, env_a);
		free_array(env_a);
		ft_putstr_fd("minishell: ", 2);
		perror(cmd->args[0]);
	}
	free_cmds(cmd);
	free_env(sh->env);
	exit(126 + (!path || errno == ENOENT));
}

static void	exec_single_builtin(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdout;
	int	out_fd;

	saved_stdout = dup(STDOUT_FILENO);
	if (cmd->out_file != NULL)
	{
		if (cmd->append)
			out_fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			out_fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_fd == -1)
		{
			shell->exit_status = 1;
			return ;
		}
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	exec_builtin(cmd, shell);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

static void	cleanup_heredocs(t_cmd *cmds)
{
	t_cmd	*curr;

	curr = cmds;
	while (curr != NULL)
	{
		if (curr->heredoc == 1 && curr->in_file != NULL)
			unlink(curr->in_file);
		curr = curr->next;
	}
}

void	execute_cmds(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*curr;
	int		fd[2];
	int		prev_fd;
	pid_t	pid;

	if (!cmds || g_sig == SIGINT)
		return ;
	if (!cmds->next && cmds->args && cmds->args[0] && is_builtin(cmds->args[0]))
		return (exec_single_builtin(cmds, shell));
	prev_fd = -1;
	curr = cmds;
	signal(SIGINT, SIG_IGN);
	while (curr)
	{
		if (curr->next && pipe(fd) == -1)
			return ;
		pid = fork();
		if (pid == 0)
			execute_child(curr, shell, fd, prev_fd);
		prev_fd = update_parent_pipes(curr, fd, prev_fd);
		curr = curr->next;
	}
	wait_for_children(shell, pid);
	signal(SIGINT, sigint_handler);
	cleanup_heredocs(cmds);
}
