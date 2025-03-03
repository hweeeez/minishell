/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:59:26 by myuen             #+#    #+#             */
/*   Updated: 2025/02/27 17:44:56 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(const char *format)
{
	ft_putstr_fd((char *)format, STDERR_FILENO);
	return (1);
}

int	print_error2(const char *format)
{
	ft_putstr_fd((char *)format, STDERR_FILENO);
	return (2);
}

void	memerr_exit(int i)
{
	ft_putstr_fd("Memory Allocation Error\n", STDERR_FILENO);
	exit (i);
}
