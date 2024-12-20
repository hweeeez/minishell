#include "minishell.h"

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
            execve(c[0], c + 1, envp);
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
