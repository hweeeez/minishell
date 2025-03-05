/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:56:24 by myuen             #+#    #+#             */
/*   Updated: 2025/02/03 15:55:22 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define EXIT_MIN "-9223372036854775808"

static void	cleanup_and_exit(t_shell **shell, int exit_code)
{
	rl_clear_history();
	cleanup_shell(shell);
	*shell = NULL;
	exit(exit_code);
}

static void	print_interactive_exit(t_shell *shell)
{
	if (isatty(STDIN_FILENO) && shell->parent)
		ft_putstr_fd("exit\n", 1);
}

static int	check_exit_arguments(t_shell **shell, char **args)
{
	if (!args || !args[0] || !args[1])
		cleanup_and_exit(shell, (*shell)->exit_status);
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (ft_strlen(args[1]) == ft_strlen(EXIT_MIN) && \
	ft_strncmp(args[1], EXIT_MIN, ft_strlen(EXIT_MIN)) == 0)
	{
		return (0);
	}
	if (!ft_isvalid_long_str(args[1], 10))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		cleanup_and_exit(shell, 2);
	}
	return (0);
}

int	ft_exit(t_shell **shell, char **args, t_exebox **exe)
{
	int		exit_code;

	if (exe != NULL)
		free_exe(exe);
	if (!shell || !*shell)
		exit(1);
	print_interactive_exit(*shell);
	if (check_exit_arguments(shell, args))
		return (1);
	exit_code = (unsigned char) ft_strtoll(args[1], NULL, 10);
	cleanup_and_exit(shell, exit_code);
	return (0);
}
