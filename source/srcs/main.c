#include "minishell.h"

int g_sig = 0;

static void sigint_handler(int sig)
{
    g_sig = sig;
    ft_putchar_fd('\n', STDOUT_FILENO);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

static void init_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}

static void shell_loop(t_shell *shell)
{
    char *input;
    t_cmd *cmds;

    input = readline("minishell$ ");
    while (input != NULL)
    {
        if (*input != '\0')
            add_history(input);
        cmds = parse_input(input, shell);
        if (cmds != NULL)
        {
            execute_cmds(cmds, shell);
            free_cmds(cmds);
        }
        free(input);
        input = readline("minishell$ ");
    }
}

int main(int ac, char **av, char **envp)
{
    t_shell shell;

    (void)ac;
    (void)av;
    shell.env = init_env(envp);
    shell.exit_status = EXIT_SUCCESS;
    init_signals();
    shell_loop(&shell);
    free_env(shell.env);
    ft_putendl_fd("exit", STDOUT_FILENO);
    return (shell.exit_status);
}