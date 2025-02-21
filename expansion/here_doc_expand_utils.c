#include "minishell.h"

char	*hd_expand_env_var(const char *var_name, t_shell *shell)
{
	char	*value;

	if (!var_name || !*var_name)
		return (ft_strdup(""));
	value = ft_getenv(var_name, shell);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*hd_get_var_name(const char *str, size_t *pos)
{
	size_t	start;
	char	*var_name;

	start = *pos;
	if (!str[start])
		return (NULL);
	if (!is_valid_first_char(str[start]))
		return (ft_strdup(""));
	while (str[*pos + 1] && is_valid_var_char(str[*pos + 1]))
		(*pos)++;
	var_name = ft_strndup(&str[start], *pos - start + 1);
	return (var_name);
}
