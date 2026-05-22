#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>            // opendir, readdir, closedir
# include <errno.h>             // errno
# include <fcntl.h>             // open
# include <readline/history.h>  // add_history
# include <readline/readline.h> // readline, on_new_line, replace_line redisplay
# include <signal.h>            // signal
# include <stdio.h>             // perror
# include <stdlib.h>            // malloc, free, exit
# include <string.h>            // strerror
# include <sys/wait.h>          // waitpid, WIFEXITED, WEXITSTATUS
# include <unistd.h>            // write, access, fork, execve, chdir, getcwd

extern int			g_sig;

# define EQUAL 0

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			**args;
	char			*in_file;
	char			*out_file;
	int				append;
	int				heredoc;
	char			*heredoc_delim;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	t_env			*env;
	int				exit_status;
}					t_shell;

# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CMD_CANNOT_EXECUTE 126

void				*ft_malloc(size_t size);
t_env				*init_env(char **envp);
void				free_env(t_env *env);
char				*get_env_val(t_env *env, char *key);
t_cmd				*parse_input(char *input, t_shell *shell);
void				free_cmds(t_cmd *cmds);
void				execute_cmds(t_cmd *cmds, t_shell *shell);
int					exec_builtin(t_cmd *cmd, t_shell *shell);

#endif