/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:16:11 by myuen             #+#    #+#             */
/*   Updated: 2025/01/29 20:55:51 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

typedef struct s_tokenizer	t_tokenizer;
typedef struct s_token	t_token;

char	*expand(t_tokenizer *tok, t_shell *shell);
char	*expand_split(t_tokenizer *tok, t_shell *shell);
int		is_valid_first_char(char c);
int		is_valid_var_char(char c);
char	*ft_getenv(const char *name, t_shell *shell);
char	*get_var_name(t_tokenizer *tok, size_t *i);
char	*word_split(const char *input);
t_token	*tokenize_expanded_string(char *expanded);

#endif
