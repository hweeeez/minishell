
#include "minishell.h"

t_token  *handle_special(t_tokenizer *tok)
{
    char c;
    char next;
    char *value;
    t_token_type type;
    
    c = tok->input[tok->position];
    next = tok->input[tok->position + 1];
    if (c == '|')
        type = TOKEN_PIPE;
    else if (c == '<' && next == '<')
    {
        type = TOKEN_HEREDOC;
        tok->position++;
    }
    else if (c == '>' && next == '>')
    {
        type = TOKEN_APPEND;
        tok->position++;
    }
    else if (c == '<')
        type = TOKEN_REDIR_IN;
    else // c == '>'
        type = TOKEN_REDIR_OUT;
    value = (char *)malloc(3);
    if (!value)
        return NULL;
    value[0] = c;
    if (type == TOKEN_HEREDOC || type == TOKEN_APPEND)
        value[1] = c;
    else
        value[1] = '\0';
    value[2] = '\0';
    tok->position++;
    return new_token(value, type);
}