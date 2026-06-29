#include "minishell.h"

void	route_child_io(t_cmd *cmd, int fd[2], int prev_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next != NULL)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

void	route_file_redirections(t_cmd *cmd)
{
	int	file_fd;

	if (cmd->in_file != NULL)
	{
		file_fd = open(cmd->in_file, O_RDONLY);
		if (file_fd == -1)
			exit(EXIT_FAILURE);
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);
	}
	if (cmd->out_file != NULL)
	{
		if (cmd->append == 1)
			file_fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			file_fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file_fd == -1)
			exit(EXIT_FAILURE);
		dup2(file_fd, STDOUT_FILENO);
		close(file_fd);
	}
}

int	update_parent_pipes(t_cmd *cmd, int fd[2], int prev_fd)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next != NULL)
	{
		close(fd[1]);
		return (fd[0]);
	}
	return (-1);
}

void	wait_for_children(t_shell *shell)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
		;
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}
