/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:19:11 by myuen             #+#    #+#             */
/*   Updated: 2025/01/16 21:15:42 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name(t_tokenizer *tok, size_t *i)
{
	size_t	start;
	char	*var_name;

	start = *i + 1;
	if (!tok->input[start])
		return (NULL);
	if (tok->input[start] == '?' || tok->input[start] == '$')
	{
		*i = start;
		return (ft_strndup(&tok->input[start], 1));
	}
	while (tok->input[*i + 1] && (ft_isalnum(tok->input[*i + 1]) || tok->input[*i + 1] == '_'))
		(*i)++;
	var_name = ft_strndup(&tok->input[start], *i - start + 1);
	return (var_name);
}

static char	*handle_expansion(t_tokenizer *tok, size_t *i, t_shell *shell)
{
	char	*var_name;
	char	*expanded;

	var_name = get_var_name(tok, i);
	if (!var_name)
		return (ft_strdup("$"));
	expanded = expand_env_var(var_name, shell);
	free(var_name);
	return (expanded);
}
static char	*expand_env_var(const char *var_name, t_shell *shell)
{
	char	*value;

	if (!var_name || !*var_name)
		return (ft_strdup("$"));
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(shell->exit_status));
	value = getenv(var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*expand_quote(t_tokenizer *tok, t_shell *shell, size_t start, size_t len)
{
	char	*value;
	char	*tmp;
	char	*expanded;
	size_t	i;

	value = ft_strdup("");
	i = start + 1;
	while (i < start + len - 1)
	{
		if (tok->quote == '"' && tok->input[i] == '$')
		{
			tmp = handle_expansion(tok, &i, shell);
	 		expanded = ft_strjoin_free(value, tmp);
			value = expanded;
		}
		else
		{
			tmp = ft_chartostr(tok->input[i]);
			expanded = ft_strjoin_free(value, tmp);
			value = expanded;
		}
		i++;
	}
	return (value);
}
