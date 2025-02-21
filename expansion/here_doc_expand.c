#include "minishell.h"

static char	*hd_expand_var(const char *input, size_t *pos, t_shell *shell)
{
	char	*var_name;
	char	*value;

	(*pos)++;
	if (input[*pos] == '?')
	{
		(*pos)++;
		return (ft_itoa(shell->exit_status));
	}
	if (!is_valid_first_char(input[*pos]))
		return (ft_strdup("$"));
	var_name = hd_get_var_name(input, pos);
	if (!var_name)
		return (ft_strdup(""));
	value = hd_expand_env_var(var_name, shell);
	free(var_name);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

static char	*process_expansion(const char *input, size_t *i, char *expanded, t_shell *shell)
{
	char	*temp;
	char	*var_value;

	var_value = hd_expand_var(input, i, shell);
	temp = expanded;
	expanded = ft_strjoin_free(expanded, var_value);
	free(temp);
	free(var_value);
	return (expanded);
}

static char	*process_literal(const char *input, size_t *i, char *expanded)
{
	char	*temp;
	char	c[2];

	c[0] = input[*i];
	c[1] = '\0';
	temp = expanded;
	expanded = ft_strjoin(expanded, c);
	free(temp);
	(*i)++;
	return (expanded);
}

char	*expand_heredoc(const char *input, t_shell *shell)
{
	size_t	i;
	char	*expanded;

	if (!input || !shell)
		return (NULL);
	expanded = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
			expanded = process_expansion(input, &i, expanded, shell);
		else
			expanded = process_literal(input, &i, expanded);
	}
	return (expanded);
}

/*
char	*expand_heredoc(const char *input, t_shell *shell)
{
	size_t	i;
	char	*expanded;
	char	*temp;
	char	*var_value;
	char	c[2];

	if (!input || !shell)
		return (NULL);
	expanded = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			var_value = hd_expand_var(input, &i, shell);
			temp = expanded;
			expanded = ft_strjoin_free(expanded, var_value);
			free(temp);
			free(var_value);
		}
		else
		{
			c[0] = input[i];
			c[1] = '\0';
			temp = expanded;
			expanded = ft_strjoin(expanded, c);
			free(temp);
			i++;
		}
	}
	return (expanded);
}*/