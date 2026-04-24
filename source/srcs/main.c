#include "minishell.h"

// Figures out exactly how many words are in the string so we know 
// how big to make our main tokens array. It's smart enough to ignore 
// spaces if they are trapped inside single or double quotes.
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
            while (str[i] != '\0' && (q != 0 || (str[i] != ' ' && str[i] != '\t')))
            {
                if ((str[i] == '"' || str[i] == '\'') && q == 0)
                    q = str[i];
                else if (q == str[i])
                    q = 0;
                i++;
            }
        }
    }
    return (count);
}

// Measures the exact length of a single word, respecting quotes, 
// so we know exactly how many bytes to ask malloc for.
int get_word_length(char *str, int i)
{
    int     len;
    char    q;

    len = 0;
    q = 0;
    while (str[i] != '\0' && (q != 0 || (str[i] != ' ' && str[i] != '\t')))
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

// Grabs memory for one specific word, copies the letters over one by one, 
// and safely caps it off with a null terminator.
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

// Our emergency cleanup crew. If a malloc fails halfway through tokenizing, 
// this destroys the partially built array so we don't leak memory.
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

// Cleans up the final completed token array after we are done using it 
// so we don't bleed memory every time the user types a command.
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

// The main engine of our lexer. It ties all the helpers together to slice up 
// the raw user input into a clean, double-pointer array ready for the execve phase.
// Example: "-l src ls" becomes ["-l", "src", "ls", NULL]
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
