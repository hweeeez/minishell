/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:46:28 by myuen             #+#    #+#             */
/*   Updated: 2025/02/01 19:52:53 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file_exists(const char *path)
{
	struct stat	s_buffer;

	if (!path)
		return (0);
	return (stat(path, &s_buffer) == 0);
}

static int	is_directory(const char *path)
{
	struct stat	s_buffer;

	if (!path || stat(path, &s_buffer) != 0)
		return (0);
	return (S_ISDIR(s_buffer.st_mode));
}

static int	is_regular_file(const char *path)
{
	struct stat	s_buffer;

	if (!path || stat(path, &s_buffer) != 0)
		return (0);
	return (S_ISREG(s_buffer.st_mode));
}

t_file_type	check_path_type(const char *path)
{
	if (!check_file_exists(path))
		return (TYPE_NONE);
	if (is_directory(path))
		return (TYPE_DIR);
	if (!is_regular_file(path))
		return (TYPE_NONE);
	if (is_executable(path))
		return (TYPE_EXECUTABLE);
	return (TYPE_FILE);
}
