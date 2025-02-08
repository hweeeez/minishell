
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
	DIR		*dir;
	char	*name;

	dir = NULL;
	name = splitdir(path);
	if (name != NULL)
	{
		dir = opendir(name);
		if (dir)
		{
			closedir(dir);
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
