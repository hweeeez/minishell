/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2024/11/04 22:00:33 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define ERR_USAGE "Usage: ./pipex infile cmd1 cmd2 outfile"
# define ERR_PIPE "Pipe error"
# define ERR_FORK "Fork error"
# define ERR_CHILD "Child Exe Error"
# define ERR_CMD "Command Error"
# define ERR_FILE "File error"

# define FILE_PERMISSION 0644
# define PATH_LINE "PATH="

# define EXIT_NORMAL 0
# define EXIT_FAILURE 1
# define EXIT_CANNOT_EXE 126
# define EXIT_NOT_FOUND 127

# define FATAL_ERR_SIG 128

typedef struct s_pipe
{
	int		pipe_fd[2];
	int		infile;
	int		outfile;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd1_args;
	char	**cmd2_args;
	char	**env;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipe;

/* ft_init.c */
int		ft_init_pipes(t_pipe *pipex, char **argv, char **envp);

/* ft_path.c */
char	*ft_find_cmd_path(char *cmd, char ***cmd_args, char **envp);

/* ft_handle_direct_path.c */
char	*ft_check_direct_path(char *cmd, char ***cmd_args);

/* ft_cmds.c */
void	ft_execute_cmd1(t_pipe *pipex);
void	ft_execute_cmd2(t_pipe *pipex);

/* ft_pipex_utils.c*/
void	ft_free_split(char ***split);
void	ft_perror_exit(t_pipe *pipex, char *msg);
void	ft_close_pipes(t_pipe *pipex);
void	ft_free_memory(t_pipe *pipex);
int		execve(pipex->cmd1_path, pipex->cmd1_args, pipex->env);pipex(int argc, char **argv, char **envp);

#endif
