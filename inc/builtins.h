/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:26:42 by myuen             #+#    #+#             */
/*   Updated: 2025/02/03 15:53:46 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_shell	t_shell;

int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_cd(t_shell *shell, char *path);
char	*get_new_cd_path(t_shell *shell, char *path);
int		ft_env(t_shell *shell);
int		ft_export(t_shell *shell, char **args);
int		ft_unset(t_shell *shell, char **args);
int		ft_exit(t_shell *shell, char **args);
int		isbuiltin(char *value);

#endif