/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:26:42 by myuen             #+#    #+#             */
/*   Updated: 2025/01/31 21:37:39 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_shell
{
	char	**env;
	int		exit_status;
	int		interactive;
	char	*cwd;
}	t_shell;

t_shell	*init_shell(char **env);
void	cleanup_shell(t_shell **shell);
char	*get_working_dir(void);

#endif
