/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_access.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:46:28 by myuen             #+#    #+#             */
/*   Updated: 2025/02/01 19:52:53 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_executable(const char *path)
{
	if (!path)
		return (0);
	return (access(path, X_OK) == 0);
}

int	has_permission(const char *path, int mode)
{
	if (!path)
		return (0);
	return (access(path, mode) == 0);
}
