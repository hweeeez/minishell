/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:19:11 by myuen             #+#    #+#             */
/*   Updated: 2025/01/30 17:55:11 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_env_var(const char *var_name, t_shell *shell)
{
	char	*value;

	if (!var_name || !*var_name)
		return (ft_strdup(""));
	value = ft_getenv(var_name, shell);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*expand(t_tokenizer *tok, t_shell *shell)
{
	char	*value;
	char	*var_name;
	size_t	start;

	value = NULL;
	start = ++(tok->position);
	if (tok->input[start] == '?')
	{
		tok->position++;
		return (ft_itoa(tok->shell->exit_status));
	}
	if (!is_valid_first_char(tok->input[start]))
		return (ft_strdup("$"));
	var_name = get_var_name(tok, &tok->position);
	if (!var_name)
		return (ft_strdup(""));
	tok->position++;
	value = expand_env_var(var_name, shell);
	free(var_name);
	return (value);
}

// static char	*handle_expansion(t_tokenizer *tok, size_t *i)
// {
// 	char	*var_name;
// 	char	*expanded;

// 	var_name = get_var_name(tok, i);
// 	if (!var_name)
// 		return (ft_strdup("$"));
// 	expanded = expand_env_var(var_name, tok->shell);
// 	free(var_name);
// 	return (expanded);
// }

// static int	append_expansion(char **value, t_tokenizer *tok, 
// 							size_t *i)
// {
// 	char	*tmp;
// 	char	*expanded;

// 	tmp = handle_expansion(tok, i);
// 	if (!tmp)
// 		return (0);
// 	expanded = ft_strjoin_free(*value, tmp);
// 	if (!expanded)
// 		return (0);
// 	*value = expanded;
// 	return (1);
// }

// static int	append_char(char **value, char c)
// {
// 	char	*tmp;
// 	char	*expanded;

// 	tmp = ft_chartostr(c);
// 	if (!tmp)
// 		return (0);
// 	expanded = ft_strjoin_free(*value, tmp);
// 	if (!expanded)
// 		return (0);
// 	*value = expanded;
// 	return (1);
// }

// char	*expand_var(t_tokenizer *tok)
// {
// 	char	*value;
// 	char	*var_name;
// 	size_t	start;

// 	start = ++(tok->position);
// 	if (tok->input[start] == '?')
// 	{
// 		tok->position++;
// 		return (ft_itoa(tok->shell->exit_status));
// 	}
// 	if (!is_valid_first_char(tok->input[start]))
// 		return (ft_strdup("$"));
// 	value = ft_strdup("");
// 	var_name = get_var_name(tok, &tok->position);
// 	if (!var_name)
// 		return (value);
// 	while ( < (start + len))
// 	{
// 		if ((tok->quote == '"' || tok->quote == 0) 
// 			&& tok->input[i] == '$')
// 		{
// 			if (!append_expansion(&value, tok, &i))
// 			{
// 				free(value);
// 				return (NULL);
// 			}
// 		}
// 		else if (!append_char(&value, tok->input[i]))
// 		{
// 			free(value);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	return (value);
// }
