#include "minishell.h"

/*void    traverse_tree(t_node** root, char** envp)
{
    if ((*root)->left)
    {
        printf("Executing left\n");
        if ((*root)->left->redirections != NULL)
            printf("Redirection: %s\n", (*root)->left->redirections->file);
        if ((*root)->left->args){
            char **c = (*root)->left->args;
            if (access(c[1], F_OK) != -1)
            	printf("File exists");
            
        }
    }
    if ((*root)->right)
    {
        if ((*root)->right->type == 0)
        {
            printf("Executing right: PIPE\n ");
            (*root) = (*root)->right;
            traverse_tree(root, envp);
        }
        else
        {
            printf("Executing right\n ");
            if ((*root)->right->redirections != NULL)
                printf("Redirection: %s\n", (*root)->right->redirections->file);
            printf("args: ");
            char **c = (*root)->right->args;
            while (*c)
            {
                printf("%s ", (*c));
                (c)++;
            }
            printf("\n");
        }
    }
}*/

int	execute(t_node *node, int input, int output, char **envp)
{
	pid_t	pid;
	pid_t	child_pid;
	int		pipefd[2];
	int		puts[2];

	if (!node)
		return (-1);
	if (node->right != NULL)
	{
		if (pipe(pipefd) == -1)
			return (-1);
	}
	pid = fork();
	puts[0] = input;
	puts[1] = output;
	if (pid == -1)
		return (-1);
	if (pid == 0)
		executechild(node, pipefd, puts, envp);
	closeputs(input, output);
	if (node->right != NULL)
	{
		close(pipefd[1]);
		child_pid = execute(node->right, pipefd[0], STDOUT_FILENO, envp);
		waitpid(pid, NULL, 0);
		waitpid(child_pid, NULL, 0);
	}
	else
		waitpid(pid, NULL, 0);
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
	else if (puts[1] != STDOUT_FILENO)
	{
		dup2(puts[1], STDOUT_FILENO);
		close(puts[1]);
	}
	if (node->left != NULL)
		c = node->left->args;
	else
		c = node->args;
	if (execve(c[0], c, envp) == -1)
		printf("%s\n Error", c[0]);
}

public void checkif_builtin(char* cmd)
		{
			if (ft_strcmp(cmd, "echo") == 1)
				return (printf("%s", "run echo"), 1);
			if (ft_strcmp(cmd, "cd") == 1)
				return (printf("%s", "run cd"), 1);
			if (ft_strcmp(cmd, "pwd") == 1)
				return (printf("%s", "run pwd");
			if (ft_strcmp(cmd, "export") == 1)
				return (printf("%s", "run export"), 1);
			if (ft_strcmp(cmd, "unset") == 1)
				return (printf("%s", "run unset"), 1);
			if (ft_strcmp(cmd, "env") == 1)
				return (printf("%s", "run env"), 1);
			if (ft_strcmp(cmd, "exit") == 1)
				return (printf("%s", "run exit"), 1);
			return (0);
		}

		public int ft_strcmp(char* str1, char* str2)
		{
			int i;

			i = 0;
			while (str1[i] != '\0')
			{
				if (str1[i] != str2[i] || str2[i] == '\0')
					return (-1);
			}
			return (1);
		}