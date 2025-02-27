/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_add_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:51:58 by hui-lim           #+#    #+#             */
/*   Updated: 2025/02/27 20:52:12 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	addpid(pid_t pid, t_exebox **con)
{
	pid_t		*temp;
	int			i;

	i = 0;
	temp = (int *)malloc(sizeof(pid_t) * ((*con)->numpid));
	if (!temp)
		memerr_exit(1);
	if ((*con)->pids != NULL)
	{
		while (i < (*con)->numpid - 1)
		{
			temp[i] = ((*con)->pids)[i];
			i++;
		}
		free((*con)->pids);
	}
	temp[i] = (pid);
	(*con)->pids = temp;
}

void	addchild(t_exe **add, t_exebox **cont)
{
	t_exe	**temp;
	int		i;

	(*cont)->numpid++;
	i = 0;
	temp = (t_exe **)malloc(sizeof(t_exe) * ((*cont)->numpid));
	if (!temp)
		memerr_exit(1);
	if ((*cont)->exes != NULL)
	{
		while (i < (*cont)->numpid - 1)
		{
			temp[i] = ((*cont)->exes)[i];
			i++;
		}
		free((*cont)->exes);
	}
	temp[i] = *add;
	((*cont)->exes) = temp;
}

void	addsig(t_sigs **add, t_exebox **cont)
{
	t_sigs	**temp;
	int		i;

	i = 0;
	temp = (t_sigs **)malloc(sizeof(t_sigs) * ((*cont)->numpid));
	if (!temp)
		memerr_exit(1);
	if ((*cont)->sigs != NULL)
	{
		while (i < (*cont)->numpid - 1)
		{
			temp[i] = ((*cont)->sigs)[i];
			i++;
		}
		free((*cont)->sigs);
	}
	temp[i] = *add;
	((*cont)->sigs) = temp;
}
