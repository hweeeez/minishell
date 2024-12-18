/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2024/12/18 20:58:40 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        return new_token(handle_quote(tok), TOKEN_WORD);
    // Handle special characters
    if (ms_is_special(tok->input[tok->position]))
        return handle_special(tok);
    // Handle regular words
    start = tok->position;
    while (tok->input[tok->position] && 
           !ms_is_whitespace(tok->input[tok->position]) && 
           !ms_is_special(tok->input[tok->position]) &&
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
        printf("Error - unclosed quotes\n");
        return NULL;
    }
    return head;
}
