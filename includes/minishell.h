/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalosta- <jalosta-@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 16:55:46 by jalosta-          #+#    #+#             */
/*   Updated: 2026/07/14 16:55:46 by jalosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_sig;

# define EQUAL 0
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CMD_CANNOT_EXECUTE 126
# define SYNTAX_ERROR 258

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			**args;
	char			*in_file;
	char			*out_file;
	int				append;
	int				heredoc;
	char			*heredoc_delim;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_env			*env;
	int				exit_status;
}	t_shell;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

// signals
void			sigint_handler(int sig);

// environment
t_env			*init_env(char **envp);
char			*get_env_val(t_env *env, char *key);
char			**env_list_to_array(t_env *env);

// lexer
int				lexer(char *input, t_token **token_list);
int				is_metachar(char c);
t_token_type	get_token_type(char *word);
t_token			*new_token(char *word, t_token_type type);
void			add_token_back(t_token **lst, t_token *new_node);

// expander
void			expander(t_token *token_list, t_shell *shell);
void			trim_quotes(t_token *token_list);
char			*expand_heredoc_line(char *line, t_shell *shell);

// parser
t_cmd			*parse_input(t_token *token_list, t_shell *shell);
t_cmd			*new_cmd(void);
int				count_args(t_token *start);
void			handle_redirections(t_cmd *cmd, t_token **curr);
void			handle_heredoc(t_cmd *cmd, t_token **curr, t_shell *shell);

// executor
void			execute_cmds(t_cmd *cmds, t_shell *shell);
char			*find_path(char *cmd, t_env *env);
void			route_child_io(t_cmd *cmd, int fd[2], int prev_fd);
void			route_file_redirections(t_cmd *cmd, t_shell *shell);
int				update_parent_pipes(t_cmd *cmd, int fd[2], int prev_fd);
void			wait_for_children(t_shell *shell, pid_t last_pid);

// builtins
int				exec_builtin(t_cmd *cmd, t_shell *shell);
void			exec_cd(t_cmd *cmd, t_shell *shell);
void			exec_echo(t_cmd *cmd, t_shell *shell);
void			exec_env(t_cmd *cmd, t_shell *shell);
void			exec_exit(t_cmd *cmd, t_shell *shell);
void			exec_export(t_cmd *cmd, t_shell *shell);
void			exec_pwd(t_cmd *cmd, t_shell *shell);
void			exec_unset(t_cmd *cmd, t_shell *shell);
void			add_or_update_env(t_shell *shell, char *arg);

// memory
void			*ft_malloc(size_t size);
void			free_env(t_env *env);
void			free_cmds(t_cmd *cmds);
void			free_tokens(t_token **lst);
void			free_array(char **arr);

#endif
