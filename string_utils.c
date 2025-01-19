/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2024/12/04 19:23:52 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/* Check if character is a whitespace */
int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

/* Check if character is a special token character */
int is_special(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

/* Skip whitespace characters */
void skip_whitespace(t_tokenizer *tok)
{
    while (tok->input[tok->position] && is_whitespace(tok->input[tok->position]))
        tok->position++;
}
