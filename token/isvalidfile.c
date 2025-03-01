/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isvalidfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:35:11 by myuen             #+#    #+#             */
/*   Updated: 2025/03/01 21:07:40 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	is_valid_wfilename(char *str)
// {
// 	char		*last_slash;
// 	char		*dir_path;
// 	struct stat	path_stat;
// 	int			result;

// 	if (!str || *str == '\0')
// 		return (0);
// 	last_slash = ft_strrchr(str, '/');
// 	if (!last_slash)
// 		return (access(".", W_OK) == 0);
// 	dir_path = ft_strndup(str, last_slash - str);
// 	if (!dir_path)
// 		return (0);
// 	result = (stat(dir_path, &path_stat) == 0 && 
// 			((path_stat.st_mode & S_IFMT) == S_IFDIR) && 
// 			(access(dir_path, W_OK) == 0));
// 	free(dir_path);
// 	return (result);
// }
int	is_valid_filename(char *str)
{
	char		*last_slash;
	char		*dir_path;
	struct stat	path_stat;
	int			result;

	if (!str || *str == '\0')
		return (0);
	last_slash = ft_strrchr(str, '/');
	if (!last_slash)
		return (access(".", W_OK) == 0);
	dir_path = ft_strndup(str, last_slash - str);
	if (!dir_path)
		return (0);
	result = (stat(dir_path, &path_stat) == 0 && \
			((path_stat.st_mode & S_IFMT) == S_IFDIR));
	free(dir_path);
	return (result);
}
// int	is_valid_filename(t_token *redir_token, char *filename)
// {
// 	if (!filename || *filename == '\0')
// 		return (0);
// 	if (ft_strcmp(filename, "/dev/null") == 0)
// 		return (1);
// 	if (redir_token->type == TOKEN_REDIR_IN)
// 		return (access(filename, R_OK) == 0);
// 	return (is_valid_wfilename(filename));
// }

// static int	is_valid_rfilename(char *str)
// {
// 	char		*last_slash;
// 	char		*dir_path;
// 	struct stat	path_stat;
// 	int			result;

// 	if (!str || *str == '\0')
// 		return (0);
// 	last_slash = ft_strrchr(str, '/');
// 	if (!last_slash)
// 		return (access(".", W_OK) == 0);
// 	dir_path = ft_strndup(str, last_slash - str);
// 	if (!dir_path)
// 		return (0);
// 	result = (stat(dir_path, &path_stat) == 0 && 
// 			((path_stat.st_mode & S_IFMT) == S_IFDIR) && 
// 			(access(dir_path, R_OK) == 0));
// 	free(dir_path);
// 	return (result);
// }
