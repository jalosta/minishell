/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:12:12 by synoshah          #+#    #+#             */
/*   Updated: 2026/07/02 14:12:12 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_heredoc_fd(char **tmp_name)
{
	static int	hd_count = 0;
	char		*num;
	int			fd;

	num = ft_itoa(hd_count++);
	*tmp_name = ft_strjoin(".heredoc.tmp.", num);
	free(num);
	unlink(*tmp_name);
	fd = open(*tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		free(*tmp_name);
	}
	return (fd);
}

static void	process_heredoc_lines(int fd, char *delim, int exp, t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (exp)
			line = expand_heredoc_line(line, shell);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	handle_heredoc(t_cmd *cmd, t_token **curr, t_shell *shell)
{
	char	*delim;
	int		fd;
	int		exp;

	*curr = (*curr)->next;
	if (!*curr || (*curr)->type != TOKEN_WORD)
		return ;
	delim = (*curr)->value;
	exp = 1;
	if (delim[0] == '\'' || delim[0] == '\"')
	{
		exp = 0;
		ft_memmove(delim, delim + 1, ft_strlen(delim));
		delim[ft_strlen(delim) - 1] = '\0';
	}
	fd = get_heredoc_fd(&cmd->in_file);
	if (fd == -1)
		return ;
	process_heredoc_lines(fd, delim, exp, shell);
	close(fd);
	cmd->heredoc = 1;
}
