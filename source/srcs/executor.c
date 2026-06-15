#include "minishell.h"

static void free_array(char **arr)
{
    int i;

    i = 0;
    while (arr && arr[i])
        free(arr[i++]);
    free(arr);
}

static char *find_path(char *cmd, t_env *env)
{
    char    *paths;
    char    **split;
    char    *executable_path;
    char    *dir_with_slash;
    int     i;

    if (access(cmd, X_OK) == 0)
        return (ft_strdup(cmd));
    paths = get_env_val(env, "PATH");
    if (paths == NULL)
        return (NULL);
    
    split = ft_split(paths, ':');
    i = 0;
    while (split != NULL && split[i] != NULL)
    {
        dir_with_slash = ft_strjoin(split[i], "/");
        executable_path = ft_strjoin(dir_with_slash, cmd);
        free(dir_with_slash);
        
        if (access(executable_path, X_OK) == 0)
        {
            free_array(split);
            return (executable_path);
        }
        free(executable_path);
        i++;
    }
    free_array(split);
    return (NULL);
}

static char **env_list_to_array(t_env *env)
{
    int     size;
    t_env   *curr;
    char    **arr;
    char    *key_prefix;

    size = 0;
    curr = env;
    while (curr != NULL)
    {
        size++;
        curr = curr->next;
    }
    arr = ft_malloc(sizeof(char *) * (size + 1));
    curr = env;
    size = 0;
    while (curr != NULL)
    {
        if (curr->value != NULL)
        {
            key_prefix = ft_strjoin(curr->key, "=");
            arr[size] = ft_strjoin(key_prefix, curr->value);
            free(key_prefix);
        }
        else
            arr[size] = ft_strdup(curr->key);
        size++;
        curr = curr->next;
    }
    arr[size] = NULL;
    return (arr);
}

static void route_child_io(t_cmd *cmd, int fd[2], int prev_fd)
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

static void execute_child(t_cmd *cmd, t_shell *shell, int fd[2], int prev_fd)
{
    char    *path;
    char    **env_arr;

    route_child_io(cmd, fd, prev_fd);
    
    if (exec_builtin(cmd, shell) == EXIT_SUCCESS)
        exit(EXIT_SUCCESS); 
        
    path = find_path(cmd->args[0], shell->env);
    if (path == NULL)
    {
        ft_putendl_fd("minishell: command not found", STDERR_FILENO);
        exit(EXIT_CMD_NOT_FOUND);
    }
    
    env_arr = env_list_to_array(shell->env);
    execve(path, cmd->args, env_arr);
    
    free_array(env_arr);
    perror("execve");
    exit(EXIT_CMD_CANNOT_EXECUTE);
}

static int update_parent_pipes(t_cmd *cmd, int fd[2], int prev_fd)
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

static void wait_for_children(t_shell *shell)
{
    int status;

    while (waitpid(-1, &status, 0) > 0);
    if (WIFEXITED(status))
        shell->exit_status = WEXITSTATUS(status);
}

void execute_cmds(t_cmd *cmds, t_shell *shell)
{
    t_cmd   *curr;
    int     fd[2];
    int     prev_fd;
    pid_t   pid;

    if (cmds == NULL || cmds->args == NULL || cmds->args[0] == NULL)
        return ;
    prev_fd = -1;
    curr = cmds;
    while (curr != NULL)
    {
        if (curr->next != NULL && pipe(fd) == -1)
        {
            perror("pipe");
            return ;
        }
        pid = fork();
        if (pid == -1)
            perror("fork");
        else if (pid == 0)
            execute_child(curr, shell, fd, prev_fd);
        else
            prev_fd = update_parent_pipes(curr, fd, prev_fd);
        curr = curr->next;
    }
    wait_for_children(shell);
}