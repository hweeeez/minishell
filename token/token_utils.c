/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2024/12/16 20:40:24 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_tokenizer(t_tokenizer *tok, const char *input)
{
    tok->input = input;
    tok->position = 0;
    tok->quote = 0;
    tok->error = 0;
}

t_token *new_token(char *value, t_token_type type)
{
    t_token *token;
    
    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = value;
    token->type = type;
    token->next = NULL;
    return token;
}

int ms_is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

int ms_is_special(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

void skip_whitespace(t_tokenizer *tok)
{
    while (tok->input[tok->position] && ms_is_whitespace(tok->input[tok->position]))
        tok->position++;
}
