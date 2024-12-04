/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2024/12/04 20:10:33 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static char *handle_quotes(t_tokenizer *tok)
{
    size_t  start;
    char    quote;
    char    *value;
    size_t  len;

    start = tok->position;
    quote = tok->input[tok->position];
    tok->position++; // Skip opening quote
    // Look for closing quote
    while (tok->input[tok->position] && tok->input[tok->position] != quote)
        tok->position++;
    if (!tok->input[tok->position]) // Unclosed quote
    {
        tok->error = 1;
        len = tok->position - start;  // Use all characters until end
    }
    else
    {
        len = tok->position - start + 1;  // Include closing quote
        tok->position++;  // Skip closing quote
    }
    value = (char *)malloc(len + 1);
    if (!value)
        return NULL;
    ft_strlcpy(value, tok->input + start, len + 1);
    return value;
}

static  t_token  *handle_special(t_tokenizer *tok)
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

static t_token *get_next_token(t_tokenizer *tok)
{
    char *value;
    size_t start;
    size_t len;

    skip_whitespace(tok);
    if (!tok->input[tok->position])
        return new_token(NULL, TOKEN_EOF);
    // Handle quotes
    if (tok->input[tok->position] == '\'' || tok->input[tok->position] == '\"')
        return new_token(handle_quotes(tok), TOKEN_WORD);
    // Handle special characters
    if (is_special(tok->input[tok->position]))
        return handle_special(tok);
    // Handle regular words
    start = tok->position;
    while (tok->input[tok->position] && 
           !is_whitespace(tok->input[tok->position]) && 
           !is_special(tok->input[tok->position]) &&
           tok->input[tok->position] != '\'' && 
           tok->input[tok->position] != '\"')
        tok->position++;
    len = tok->position - start;
    value = (char *)malloc(len + 1);
    if (!value)
        return NULL;
    ft_strlcpy(value, tok->input + start, len + 1); // pls check if null is applied
    return new_token(value, TOKEN_WORD);
}

/* Tokenize input string */
t_token *tokenize(const char *input)
{
    t_tokenizer tok;
    t_token *head = NULL;
    t_token *current = NULL;
    t_token *new;
    
    init_tokenizer(&tok, input);
    while (!tok.error)
    {
        new = get_next_token(&tok);
        if (!new)
        {
            free_token_list(head);
            return NULL;
        }
        if (new->type == TOKEN_EOF)
        {
            free(new);
            break;
        }
        if (!head)
            head = new;
        else
            current->next = new;
        current = new;
    }
    if (tok.error)
    {
        free_token_list(head);
        printf("Possible unclosed quotes Error\n");
        return NULL;
    }
    return head;
}
