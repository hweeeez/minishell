/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2024/12/04 19:28:27 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>

typedef enum e_token_type
{
    TOKEN_WORD,       // Regular word/command/argument
    TOKEN_PIPE,       // |
    TOKEN_REDIR_IN,   // <
    TOKEN_REDIR_OUT,  // >
    TOKEN_APPEND,     // >>
    TOKEN_HEREDOC,    // <<
    TOKEN_EOF        // End of input
} t_token_type;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
} t_token;

typedef struct s_tokenizer
{
    const char  *input;     // Input string
    size_t      position;   // Current position
    char        quote;      // Current quote character (' or " or 0)
    int         error;      // Error state
} t_tokenizer;

void init_tokenizer(t_tokenizer *tok, const char *input);
t_token *new_token(char *value, t_token_type type);

int is_whitespace(char c);
int is_special(char c);
void skip_whitespace(t_tokenizer *tok);

t_token *tokenize(const char *input);
void free_token_list(t_token *head);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif