/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2025/01/18 17:56:39 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

/************************************/
/*			enum					*/
/************************************/
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF,
	TOKEN_ERROR,
}	t_token_type;

/************************************/
/*			Structures				*/
/************************************/
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_tokenizer
{
	const char	*input;
	size_t		position;
	char		quote;
	int			error;
	t_shell		*shell;
}	t_tokenizer;

void	init_tokenizer(t_tokenizer *tok, const char *input, t_shell *shell);
t_token	*new_token(char *value, t_token_type type);
int		ms_is_whitespace(char c);
int		ms_is_special(char c);
void	skip_whitespace(t_tokenizer *tok);
int		tokenize(const char *input, t_token **head, t_shell *shell);
void	free_token_list(t_token **head);
t_token	*ft_tokenlast(t_token *lst);
t_token	*handle_special_token(t_tokenizer *tok);
t_token	*handle_word_token(t_tokenizer *tok);
char	*handle_quote(t_tokenizer *tok);

#endif
/*
    TOKEN_WORD,       // Regular word/command/argument
    TOKEN_PIPE,       // |
    TOKEN_REDIR_IN,   // <
    TOKEN_REDIR_OUT,  // >
    TOKEN_APPEND,     // >>
    TOKEN_HEREDOC,    // <<
    TOKEN_EOF        // End of input
*/
