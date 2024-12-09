/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2024/12/04 18:46:21 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

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
