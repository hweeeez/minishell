/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbulitin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:56:24 by myuen             #+#    #+#             */
/*   Updated: 2025/02/03 16:00:57 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isbuiltin(char *value)
{
	if (value && *value)
	{
		if (ft_strcmp(value, "echo") == 1)
			return (1);
		if (ft_strcmp(value, "cd") == 1)
			return (1);
		if (ft_strcmp(value, "pwd") == 1)
			return (1);
		if (ft_strcmp(value, "export") == 1)
			return (1);
		if (ft_strcmp(value, "unset") == 1)
			return (1);
		if (ft_strcmp(value, "env") == 1)
			return (1);
		if (ft_strcmp(value, "exit") == 1)
			return (1);
		if (ft_strcmp(value, ".") == 1)
			return (1);
		if (ft_strcmp(value, "..") == 1)
			return (1);
	}
	return (0);
}
