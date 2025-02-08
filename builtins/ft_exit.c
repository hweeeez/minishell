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

int	ft_exit(t_shell *shell, char **args)
{
	int	exit_code;

	ft_putstr_fd("exit\n", 1);
	if (!args[1])
		exit(shell->exit_status);
	if (!ft_isvalid_integer_str(args[1], 10))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		exit(255);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_code = ft_atoi(args[1]) % 256;
	exit(exit_code);
}
