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
static char	*get_variable_name(t_tokenizer *tok, size_t *start)
{
	char	*var_name;

	if (!is_valid_first_char(tok->input[*start]))
		return (ft_strdup("$"));
	var_name = get_var_name(tok, &tok->position);
	if (!var_name)
		return (ft_strdup(""));
	//printf("var_name #%s#\n", var_name);
	//printf("tok->pos #%c#\n", tok->input[tok->position]);
	tok->position++;
	return (var_name);
}

char	*expand(t_tokenizer *tok, t_shell *shell)
{
	char	*value;
	char	*var_name;
	size_t	start;

	value = NULL;
	start = ++(tok->position);
	//printf("expand start = %ld, input[start] = %c\n", tok->position, tok->input[tok->position]);
	if (tok->input[start] == '?')
	{
		tok->position++;
		if (!shell)
			return (ft_strdup(""));
		return (ft_itoa(shell->exit_status));
	}
	var_name = get_variable_name(tok, &start);
	if (!var_name)
		return (ft_strdup(""));
	//tok->position++;
	value = expand_env_var(var_name, shell);
	free(var_name);
	return (value);
}

char	*expand_split(t_tokenizer *tok, t_shell *shell)
{
	char	*value;
	char	*var_name;
	char	*trimmed_value;
	size_t	start;

	value = NULL;
	start = ++(tok->position);
	if (tok->input[start] == '?')
	{
		tok->position++;
		if (!shell)
			return (ft_strdup(""));
		return (ft_itoa(shell->exit_status));
	}
	var_name = get_variable_name(tok, &start);
	if (!var_name)
		return (ft_strdup(""));
	//printf("var_name = #%s# expand_split = %ld, input[pos] = %c\n", var_name, tok->position, tok->input[tok->position]);
	//tok->position++;
	//printf("var_name = #%s# expand_split = %ld, input[pos] = %c\n", var_name, tok->position, tok->input[tok->position]);
	value = expand_env_var(var_name, shell);
	free(var_name);
	if (value)
	{
		trimmed_value = word_split(value);
		free(value);
		return (trimmed_value);
	}
	return (ft_strdup(""));
}
t_token	*tokenize_expanded_string(char *expanded)
{
	t_token	*token_head;
	t_token	*token;
	char	**split;
	int		i;

	if (!expanded)
		return (NULL);
	split = ft_split(expanded, ' ');
	if (!split)
		return (NULL);
	token_head = NULL;
	i = 0;
	while (split[i])
	{
		token = new_token(split[i], TOKEN_WORD);
		if (!token)
		{
			free_token_list(&token_head);
			freestrl(split);
			return (NULL);
		}
		add_token(token_head, token);
		i++;
	}
	freestrl(split);
	return (token_head);
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
