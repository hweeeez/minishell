
#include "tokenizer.h"

int main(int argc, char **argv)
{
    t_token *tokens;
    t_token *current;

    if (argc != 2)
    {
        printf("Usage: %s \"command string\"\n", argv[0]);
        return (1);
    }

    tokens = tokenize(argv[1]);
    if (!tokens)
    {
        printf("Error: Failed to tokenize input\n");
        return (1);
    }

    // Process tokens
    current = tokens;
    while (current)
    {
        printf("%s:%u\n", current->value,current->type);
        current = current->next;
    }

    // Free tokens
    while (tokens)
    {
        current = tokens;
        tokens = tokens->next;
        free(current->value);
        free(current);
    }

    return (0);
}