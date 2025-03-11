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

// static char	*splitdir(char *path)
// {
// 	int		i;
// 	char	*dir;

// 	i = 2;
// 	dir = NULL;
// 	if (!path)
// 		return (0);
// 	if (path[0] == '.' && path[1] == '/')
// 	{
// 		while (path[i] != '\0' && path[i] != '/')
// 		{
// 			i++;
// 		}
// 		path += 2;
// 		dir = ft_strcpy(path, i - 2);
// 		return (dir);
// 	}
// 	return (NULL);
// }

static int	get_dir_length(char *path)
{
	int	i;

	i = 0;
	if (!path)
		return (0);
	if (path[0] == '.' && path[1] == '/')
	{
		path += 2;
		while (path[i] != '\0' && path[i] != '/')
			i++;
		return (i);
	}
	return (0);
}

static char	*splitdir(char *path)
{
	int		i;
	int		j;
	char	*dir;

	dir = NULL;
	if (!path)
		return (NULL);
	if (path[0] == '.' && path[1] == '/')
	{
		i = get_dir_length(path);
		path += 2;
		dir = malloc(i + 1);
		if (!dir)
			return (NULL);
		j = 0;
		while (j < i)
		{
			dir[j] = path[j];
			j++;
		}
		dir[j] = '\0';
		return (dir);
	}
	return (NULL);
}

int	check_dir_exists(char *path)
{
	char	*name;
	int		result;

	name = splitdir(path);
	result = 1;
	if (name != NULL)
	{
		if (check_path_type(name) == TYPE_DIR)
		{
			result = 1;
		}
		else if (errno == ENOENT)
		{
			perror("Error");
			result = 0;
		}
		free(name);
		return (result);
	}
	return (result);
}

// int	check_dir_exists(char *path)
// {
// 	char	*name;

// 	name = splitdir(path);
// 	if (name != NULL)
// 	{
// 		if (check_path_type(name) == TYPE_DIR)
// 		{
// 			return (1);
// 		}
// 		else if (ENOENT == errno)
// 		{
// 			perror("Error");
// 			return (0);
// 		}
// 	}
// 	return (1);
// }
