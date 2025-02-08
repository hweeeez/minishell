/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:19:11 by myuen             #+#    #+#             */
/*   Updated: 2025/01/30 17:36:36 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_first_char(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

char	*ft_getenv(const char *name, t_shell *shell)
{
	int		i;
	size_t	len;

	if (!name || !shell || !shell->env)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0 && \
			shell->env[i][len] == '=')
			return (shell->env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*get_var_name(t_tokenizer *tok, size_t *pos)
{
	size_t	start;
	char	*var_name;

	start = *pos;
	if (!tok->input[start])
		return (NULL);
	if (!is_valid_first_char(tok->input[start]))
		return (ft_strdup(""));
	while (tok->input[*pos + 1] && is_valid_var_char(tok->input[*pos + 1]))
		(*pos)++;
	var_name = ft_strndup(&tok->input[start], *pos - start + 1);
	return (var_name);
}
