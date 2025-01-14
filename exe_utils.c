/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:10:54 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/14 21:10:56 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_coredump_msg(int status, int *flag)
{
    if (WIFSIGNALED(status))
	{
		if (*flag == 0 && WCOREDUMP(status))
		{
			*flag = 1;
            write(1, "Quit (core dumped)", 18);
		}
        write (1, "\n", 1);
	}
}
