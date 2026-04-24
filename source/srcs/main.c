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

// Core lexer function. Slices the raw input string into an array of tokens.
// Example: "ls>file" becomes ["ls", ">", "file", NULL]
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
    if (words == -1) // Check for syntax error (unclosed quotes)
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

int main(int ac, char **av)
{
    char    *input;
    char    **tokens;
    int     i;

    (void)ac;
    (void)av;
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
