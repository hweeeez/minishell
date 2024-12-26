#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
void    traverse_tree(t_node** root, char** envp)
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
}

int execute(t_node *node, int input, int output, char** envp)
{
	pid_t	pid;
	pid_t	child_pid;
	int pipefd[2];
	char **c;
	
	if (!node)
		return (-1);
	if (node->right != NULL)
	{
		if (pipe(pipefd) == -1) 
		{
            perror("pipe");
            return (-1);
        }
	}
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (input != STDIN_FILENO)
		{
			dup2(input, STDIN_FILENO);
			close(input);
		}
		if (node->right != NULL)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		else if (output != STDOUT_FILENO)
		{
			dup2(output, STDOUT_FILENO);
			close(output);
		}
		if (node->left != NULL)
			c = node->left->args;
		else
			c = node->args;
		execve(c[0], c, envp);
	}
	if (input != STDIN_FILENO) close(input);
    if (output != STDOUT_FILENO) close(output);
	if (node->right != NULL)
	{
	char buffer[1024];
        ssize_t bytesRead;

        // Read from STDIN (which is now connected to the pipe)
        while ((bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, bytesRead);  // Print to stdout
        }
		//child_pid = execute(node->right, pipefd[0], STDOUT_FILENO, envp);
		waitpid(pid, NULL, 0);
		//waitpid(child_pid, NULL, 0);
	}
	else
		waitpid(pid, NULL, 0);
	return (pid);
}

/*int execute(t_node *node, int input, int output, char** envp)
{
	pid_t pid;
	if ((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    }
	char **c = node->left->args;
    if (pid == 0) {  // Child process
        execve(c[0], c, envp);
        perror("execve");  // Only reaches here if exec fails
        exit(1);
    }

    // Parent process
    waitpid(pid, NULL, 0);  // Wait for child to finish
    return 0;
}*/

