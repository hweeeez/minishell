/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:56:24 by myuen             #+#    #+#             */
/*   Updated: 2025/02/02 21:02:30 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_name(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell && shell->env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(shell->env[i], STDOUT_FILENO);
		i++;
	}
}

static void	print_identifier_error(char *arg)
{
	ft_putstr_fd("export: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static int	handle_arg(t_shell *shell, char *arg)
{
	char	*key;
	char	*value;
	char	*equals;
	int		result;

	if (!is_valid_name(arg))
		return (print_identifier_error(arg), 1);
	equals = ft_strchr(arg, '=');
	if (!equals)
		return (0);
	key = ft_strndup(arg, equals - arg);
	value = ft_strdup(equals + 1);
	if (!key || !value)
		return (free(key), free(value), 1);
	result = update_env(shell, key, value);
	free(key);
	free(value);
	return (result);
}

int	ft_export(t_shell *shell, char **args)
{
	int	i;
	int	status;

	//ft_putstr_fd("--minishell export--\n", STDOUT_FILENO);
	if (!args[1])
	{
		print_env(shell);
		return (0);
	}
	status = 0;
	i = 1;
	while (args[i])
	{
		if (handle_arg(shell, args[i]))
			status = 1;
		i++;
	}
	return (status);
}
