#include "minishell.h"


// Counts the total number of words to allocate the tokens array.
// It skips spaces inside quotes, treats operators (<, >, |, <<, >>) 
// as separate tokens, and checks for unclosed quotes.
int count_words(char *str)
{
    int     count;
    int     i;
    char    q;

    count = 0;
    i = 0;
    q = 0;
    while (str[i] != '\0')
    {
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        if (str[i] != '\0')
        {
            count++;
            if (str[i] == '<' || str[i] == '>' || str[i] == '|')
            {
                if (str[i] == str[i + 1] && str[i] != '|')  // Handle double operators (>> or <<)
                    i += 2;
                else
                    i++;
            }
            else
            {
                while (str[i] != '\0' && (q != 0 || (str[i] != ' ' && str[i] != '\t' && 
                        str[i] != '<' && str[i] != '>' && str[i] != '|')))
                {
                    if ((str[i] == '"' || str[i] == '\'') && q == 0)
                        q = str[i];
                    else if (q == str[i])
                        q = 0;
                    i++;
                }
            }
        }
    }
    if (q != 0) // If q is not 0, a quote was left open.
    {
        printf("unclosed quote\n");
        return (-1);
    }
    return (count);
}

// Gets the length of the current word for malloc.
// Returns 1 or 2 immediately for operators, and stops counting 
// if a normal word hits a space or an operator.
int get_word_length(char *str, int i)
{
    int     len;
    char    q;

    len = 0;
    q = 0;
    if (str[i] == '<' || str[i] == '>' || str[i] == '|')
    {
        if (str[i] == str[i + 1] && str[i] != '|')
            return (2);
        return (1);
    }
    while (str[i] != '\0' && (q != 0 || (str[i] != ' ' && str[i] != '\t' && 
        str[i] != '<' && str[i] != '>' && str[i] != '|')))
    {
        if ((str[i] == '"' || str[i] == '\'') && q == 0)
            q = str[i];
        else if (q == str[i])
            q = 0;
        len++;
        i++;
    }
    return (len);
}

// Allocates memory and copies a single word from the input string.
char *allocate_word(char *str, int start, int len)
{
    char    *word;
    int     k;

    word = malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    k = 0;
    while (len > 0)
    {
        word[k] = str[start];
        k++;
        start++;
        len--;
    }
    word[k] = '\0';
    return (word);
}

// Frees the partially built token array if a malloc fails.
void free_tokens(char **tokens, int current_j)
{
    int i;

    i = 0;
    while (i < current_j)
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

// Frees the completed token array to prevent memory leaks.
void free_array(char **array)
{
    int i;

    i = 0;
    if (!array)
        return ;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

// Our lexer function. Slices the input string into an array of tokens.
// Example -  "ls>file" becomes ["ls", ">", "file", NULL]
char **tokenize_input(char *input)
{
    int     words;
    char    **tokens;
    int     i;
    int     j;
    int     len;

    i = 0;
    j = 0;
    words = count_words(input);
    if (words == -1) // Check for syntax error (unclosed quotes). Look at the first functions error check near the end.
        return NULL;
    tokens = malloc(sizeof(char *) * (words + 1));
    if (!tokens)
        return (NULL);
    while (input[i] != '\0')
    {
        while (input[i] == ' ' || input[i] == '\t')
            i++;
        if (input[i] != '\0')
        {
            len = get_word_length(input, i);
            tokens[j] = allocate_word(input, i, len);
            if (!tokens[j])
            {
                free_tokens(tokens, j);
                return (NULL);
            }
            i = i + len;
            j++;
        }
    }
    tokens[j] = NULL;
    return (tokens);
}

// Creates a dynamic duplicate of the system's environment variables 
// so we have memory space to modify them later.
char **copy_env(char **envp)
{
    int     i;
    int     count;
    char    **new_env;

    i = 0;
    count = 0;
    while (envp[count] != NULL)
        count++;
    new_env = malloc(sizeof(char *) * (count + 1));
    if (!new_env)
        return (NULL);
    while (i < count)
    {
        new_env[i] = ft_strdup(envp[i]);
        i++;
    }
    new_env[i] = NULL;
    return (new_env);
}

// Searches our environment array for a specific variable and returns its value.
char *get_env_value(char *var_name, char **env)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(var_name); 
    while (env[i] != NULL)
    {
        // We check for the '=' to create a hard boundary. This prevents false matches 
        // like searching for "USER" and accidentally matching "USER_ID=12345.""
        if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
            return (env[i] + len + 1);
        i++;
    }
    return (NULL);
}

// Makes a new string by swapping a variable with its environment value.
// i = index of the '$'
// j = length of the variable name
// The prefix would be for example  "Hello " in "Hello $USER".
// The suffix would be for example  "!" in "Hello $USER!".
char *replace_string(char *token, char *value, int i, int j)
{
    int     prefix_len;
    int     value_len;
    int     suffix_len;
    char    *new_str;
    int     k;
    int     m;

    prefix_len = i;
    value_len = 0;
    k = 0;
    m = 0;
    if (value)
        value_len = ft_strlen(value);
    suffix_len = ft_strlen(token + i + 1 + j);
    new_str = malloc(sizeof(char) * (prefix_len + value_len + suffix_len + 1));
    if (!new_str)
        return (NULL);
    while (k < prefix_len)
    {
        new_str[k] = token[k];
        k++;
    }
    while (m < value_len)
        new_str[k++] = value[m++];
    m = i + 1 + j;
    while (token[m] != '\0')
        new_str[k++] = token[m++];
    new_str[k] = '\0';
    free(token);
    return (new_str);
}

// Checks a token for the '$' sign to expand environment variables.
// Protects the $ if it's wrapped in single quotes.
char *expand_token(char *token, char **env)
{
    int     i = 0;
    char    var[100];
    int     j;
    char    *value;
    char    q = 0;
    int     dollar_idx;

    while (token[i])
    {
        if ((token[i] == '"' || token[i] == '\'') && q == 0)
            q = token[i];
        else if (q == token[i])
            q = 0;
        if (token[i] == '$' && q != '\'')
        {
            dollar_idx = i;
            i++;
            j = 0;
            while (token[i] && ((token[i] >= 'a' && token[i] <= 'z') ||
                   (token[i] >= 'A' && token[i] <= 'Z') ||
                   (token[i] >= '0' && token[i] <= '9') || token[i] == '_'))
                var[j++] = token[i++];
            var[j] = '\0';
            value = get_env_value(var, env);
            token = replace_string(token, value, dollar_idx, j);
            if (!token)
                return (NULL);
            if (value)
                i = dollar_idx + ft_strlen(value) - 1; 
            else
                i = dollar_idx - 1;
        }
        i++;
    }
    return (token);
}

// envp acts like av, but instead of holding user typed arguments, 
// it holds the systems background state (environment variables) .
// We use this to find things like $USER or the PATH for executing commands.
int main(int ac, char **av, char **envp)
{
    char    *input;
    char    **tokens;
    char    **my_env;
    int     i;

    (void)ac;
    (void)av;
    my_env = copy_env(envp);
    if (!my_env)
        return 1;
    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
        {
            printf("exit\n");
            break ;
        }
        if (input[0] != '\0')
        {
            add_history(input);
            tokens = tokenize_input(input);
            i = 0;
            if (tokens)
            {
                while (tokens[i])
                {
                    tokens[i] = expand_token(tokens[i], my_env);
                    printf("Token %d: [%s]\n", i, tokens[i]);
                    i++;
                }
                free_array(tokens);
            }
        }
        free(input);
    }
    return (0);
}