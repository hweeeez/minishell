/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:26:42 by myuen             #+#    #+#             */
/*   Updated: 2025/02/01 21:22:33 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_token	t_token;
typedef struct s_node	t_node;

typedef struct s_shell
{
	char					**env;
	volatile int			exit_status;
	pid_t					parent;
	t_token					*token;
	t_node					*tree;
	t_node					*root;
	int						expand_flag;
}	t_shell;

typedef enum e_file_type
{
	TYPE_NONE,
	TYPE_FILE,
	TYPE_DIR,
	TYPE_EXECUTABLE
}	t_file_type;

t_shell		*init_shell(char **env);
void		cleanup_shell(t_shell **shell);
char		*get_working_dir(void);
char		*get_env_value(t_shell *shell, const char *key);
int			update_env(t_shell *shell, const char *key, const char *value);
t_file_type	check_path_type(const char *path);
int			is_executable(const char *path);
int			has_permission(const char *path, int mode);

#endif
