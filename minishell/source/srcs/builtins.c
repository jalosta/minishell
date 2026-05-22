#include "minishell.h"

t_builtin get_builtin_type(char *cmd)
{
    if (ft_strncmp(cmd, "cd", 3) == EQUAL)
        return (BUILTIN_CD);
    if (ft_strncmp(cmd, "pwd", 4) == EQUAL)
        return (BUILTIN_PWD);
    if (ft_strncmp(cmd, "export", 7) == EQUAL)
        return (BUILTIN_EXPORT);
    if (ft_strncmp(cmd, "unset", 6) == EQUAL)
        return (BUILTIN_UNSET);
    if (ft_strncmp(cmd, "env", 4) == EQUAL)
        return (BUILTIN_ENV);
    if (ft_strncmp(cmd, "exit", 5) == EQUAL)
        return (BUILTIN_EXIT);
    return (BUILTIN_NONE);
}

static void exec_cd(t_cmd *cmd, t_shell *shell)
{
    if (cmd->args[1] == NULL)
        return ;
    if (chdir(cmd->args[1]) != 0)
    {
        perror("minishell: cd");
        shell->exit_status = EXIT_FAILURE;
    }
    else
        shell->exit_status = EXIT_SUCCESS;
}

static void exec_env(t_shell *shell)
{
    t_env *curr;

    curr = shell->env;
    while (curr != NULL)
    {
        if (curr->value != NULL)
        {
            ft_putstr_fd(curr->key, STDOUT_FILENO);
            ft_putchar_fd('=', STDOUT_FILENO);
            ft_putendl_fd(curr->value, STDOUT_FILENO);
        }
        curr = curr->next;
    }
    shell->exit_status = EXIT_SUCCESS;
}

static void exec_pwd(t_shell *shell)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (cwd != NULL)
    {
        ft_putendl_fd(cwd, STDOUT_FILENO);
        free(cwd);
        shell->exit_status = EXIT_SUCCESS;
    }
    else
    {
        perror("minishell: pwd");
        shell->exit_status = EXIT_FAILURE;
    }
}

void exec_builtin(t_cmd *cmd, t_shell *shell)
{
    t_builtin type;

    type = get_builtin_type(cmd->args[0]);
    if (type == BUILTIN_CD)
        exec_cd(cmd, shell);
    else if (type == BUILTIN_ENV)
        exec_env(shell);
    else if (type == BUILTIN_PWD)
        exec_pwd(shell);
    else if (type == BUILTIN_EXIT)
    {
        free_cmds(cmd);
        free_env(shell->env);
        exit(shell->exit_status);
    }
}