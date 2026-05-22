#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>             // perror
# include <stdlib.h>            // malloc, free, exit
# include <unistd.h>            // write, access, fork, execve, chdir, getcwd
# include <fcntl.h>             // open
# include <sys/wait.h>          // waitpid, WIFEXITED, WEXITSTATUS
# include <signal.h>            // signal
# include <dirent.h>            // opendir, readdir, closedir
# include <string.h>            // strerror
# include <errno.h>             // errno
# include <readline/readline.h> // readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>  // add_history
# include "libft/libft.h"

extern int g_sig;

#define EQUAL 0

typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_cmd {
    char **args;
    char *in_file;
    char *out_file;
    int append;
    int heredoc;
    char *heredoc_delim;
    struct s_cmd *next;
} t_cmd;

typedef struct s_shell {
    t_env *env;
    int exit_status;
} t_shell;

# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CMD_CANNOT_EXECUTE 126

typedef enum e_builtin {
    BUILTIN_NONE,
    BUILTIN_CD,
    BUILTIN_PWD,
    BUILTIN_EXPORT,
    BUILTIN_UNSET,
    BUILTIN_ENV,
    BUILTIN_EXIT
} t_builtin;

void *ft_malloc(size_t size);
t_env *init_env(char **envp);
void free_env(t_env *env);
char *get_env_val(t_env *env, char *key);
t_cmd *parse_input(char *input, t_shell *shell);
void free_cmds(t_cmd *cmds);
void execute_cmds(t_cmd *cmds, t_shell *shell);
t_builtin get_builtin_type(char *cmd);
void exec_builtin(t_cmd *cmd, t_shell *shell);

#endif