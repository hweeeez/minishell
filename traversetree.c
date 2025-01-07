#include "minishell.h"

int	execute(t_node *node, char **envp)
{
	char	**cmd;
	int		input;

	if (node->type == 0)
	{
		cmd = node->left->args;
		if (checkif_builtin(cmd[0]) == 0)
		{
			if (node->left->rootredir != NULL)
			{
				//need to account for multiple redir in
				if (node->left->rootredir->type == TOKEN_REDIR_IN)
				{
					input = get_redir(node->left->rootredir);
					node->left->redirs = node->left->rootredir->next;
				}
				else if (node->left->rootredir->type == TOKEN_HEREDOC)
					return (2);
			}
			else
			{
				node->left->redirs = node->left->rootredir;
				input = STDIN_FILENO;
			}
			exe_commands(node, input, STDOUT_FILENO, envp);
		}
	}
	return (0);
}

static void quitchild(int sig)
{
	exit(0);
}

int	exe_commands(t_node *node, int input, int output, char **envp)
{
	pid_t	pid;
	pid_t	child_pid;
	int		pipefd[2];
	int		puts[2];
	int		status;
	struct	sigaction ign;
	struct	sigaction quit;
	struct	sigaction sig_int;
	static int		flag = 0;

	ign.sa_handler = SIG_IGN;
	sig_int.sa_handler = quitchild;
	child_pid = 0;
	if (node->right != NULL || node->left->redirs != NULL)
	{
		flag = 0;
		if (pipe(pipefd) == -1)
			return (-1);
	}
	pid = fork();
	puts[0] = input;
	puts[1] = output;
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		sigaction(SIGQUIT, &quit, NULL);
		sigaction(SIGINT, &sig_int, NULL);
		executechild(node, pipefd, puts, envp);
	}
	else if (pid > 0)
	{
		sigaction(SIGINT, &ign, NULL);
	}
	closeputs(input, output);
	if (node->right != NULL)
	{
		close(pipefd[1]);
		child_pid = exe_commands(node->right, pipefd[0], STDOUT_FILENO, envp);
		waitpid(pid, &status, 0);
		waitpid(child_pid, NULL, 0);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	//set a flag to check whether message has been printed
	if (WIFSIGNALED(status))
	{
		if (flag == 0)
		{
			flag = 1;
			if (WCOREDUMP(status))
				write(1, "Quit (core dumped)", 18);
			write (1, "\n", 1);
		}
	}
	return (pid);
}

void	closeputs(int input, int output)
{
	if (input != STDIN_FILENO)
		close(input);
    if (output != STDOUT_FILENO)
		close(output);
}

void	executechild(t_node *node, int pipefd[2], int puts[2], char **envp)
{
	char	**c;

	if (puts[0] != STDIN_FILENO)
	{
		dup2(puts[0], STDIN_FILENO);
		close(puts[0]);
	}
	if (node->right != NULL)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else if (node->left->redirs != NULL)
	{
		int	filefd = get_redir(node->left->redirs);
		dup2(filefd, STDOUT_FILENO);
		close(filefd);
	}
	c = node->left->args;
	if (execve(c[0], c, envp) == -1)
		printf("Error%s\n", c[0]);
}
//cat notes.txt > a.txt > b.txt > c.txt
int	get_redir(t_redir *redir)
{
	int	filefd;

	filefd = -1;
	if (redir != NULL)
	{
		if (redir->type == TOKEN_REDIR_OUT)
			filefd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == TOKEN_APPEND)
			filefd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == TOKEN_REDIR_IN)
			filefd = open(redir->file, O_RDONLY, 0644);
		if (redir->next == NULL)
			return (filefd);
		else
			return (get_redir(redir->next));
	}
	return (filefd);
}

int checkif_builtin(char* cmd)
{
	if (ft_strcmp(cmd, "echo") == 1)
		return ((printf("%s\n", "run echo")), 1);
	if (ft_strcmp(cmd, "cd") == 1)
		return (printf("%s\n", "run cd"), 1);
	if (ft_strcmp(cmd, "pwd") == 1)
		return (get_pwd(), 1);
	if (ft_strcmp(cmd, "export") == 1)
		return (printf("%s\n", "run export"), 1);
	if (ft_strcmp(cmd, "unset") == 1)
		return (printf("%s\n", "run unset"), 1);
	if (ft_strcmp(cmd, "env") == 1)
		return (printf("%s\n", "run env"), 1);
	if (ft_strcmp(cmd, "exit") == 1)
		return (printf("%s\n", "run exit"), 1);
	return (0);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] != str2[i] || str2[i] == '\0')
			return (-1);
		i++;
	}
	return (1);
}