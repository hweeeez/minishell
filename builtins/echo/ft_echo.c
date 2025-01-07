/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:19:26 by myuen             #+#    #+#             */
/*   Updated: 2025/01/07 21:27:58 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(const char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	handle_printing(const char *str)
{
	return ;
}

int	ft_echo(char **args)
{
	int	i;
	int	print_newline;

	print_newline = 1;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		print_newline = 0;
		i++;
	}
	while (args[i])
	{
		handle_printing(args[i]);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (print_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
/*
Quote parsing rules:

Single quotes ('): Everything is literal, no expansion
Double quotes ("): Expand variables but keep other characters literal
Mixed quotes: Need to know which quote context we're in
Adjacent strings: Need to be concatenated


Variable expansion:
$VAR expands outside quotes or in double quotes
$VAR stays literal in single quotes
$? for exit status

Variable naming rules:
First character must be:
--letter (a-z, A-Z) or
--underscore (_)
Rest of name can be:
--letters
--numbers
--underscores

*/
