/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:16:11 by myuen             #+#    #+#             */
/*   Updated: 2025/01/17 18:38:43 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

typedef struct s_tokenizer	t_tokenizer;

char	*expand_tok(t_tokenizer *tok, size_t start, size_t len);
int		is_valid_first_char(char c);
int		is_valid_var_char(char c);
char	*ft_getenv(const char *name, t_shell *shell);
char	*get_var_name(t_tokenizer *tok, size_t *i);

#endif
