/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direxists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:47:19 by hui-lim           #+#    #+#             */
/*   Updated: 2025/02/27 21:47:21 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*splitdir(char *path)
{
	int		i;
	char	*dir;

	i = 2;
	dir = NULL;
	if (!path)
		return (0);
	if (path[0] == '.' && path[1] == '/')
	{
		while (path[i] != '\0' && path[i] != '/')
		{
			i++;
		}
		path += 2;
		dir = ft_strcpy(path, i - 2);
		return (dir);
	}
	return (NULL);
}

int	check_dir_exists(char *path)
{
	char	*name;

	name = splitdir(path);
	if (name != NULL)
	{
		if (check_path_type(name) == TYPE_DIR)
		{
			return (1);
		}
		else if (ENOENT == errno)
		{
			perror("Error");
			return (0);
		}
	}
	return (1);
}
