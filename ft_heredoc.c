#include "minishell.h"

//read line first, if line contains token heredoc

static pid_t    exe_hd(t_node *node, int filefd, char **envp)
{
    int pid;
    pid = fork();
    if (pid == 0)
    {
        dup2(filefd, STDIN_FILENO);
        close(filefd);
        if (execve(node->args[0], node->args, envp) == -1)
            printf("Error\n");
    }
    return (pid);
}

int ft_heredoc(t_node *node, char **envp)
{
    pid_t   childpid;
    char    *s;
    int     filefd;

    //need to figure out how to use exe_command to accomodate for redirs also
    filefd = open("hd.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    while (1)
    {
        s = readline("> ");
        if (s != NULL)
        {
            if (ft_strcmp(s, node->redirs->file) == 1)
            {
                free(s);
                close(filefd);
                break;
            }
            write(filefd, s, ft_strlen(s));
            write(filefd, "\n", 1);
        }
        free(s);
    }   
    filefd = open("hd.txt", O_RDONLY, 0644);
    childpid = exe_hd(node, filefd, envp);
    node->redirs = node->redirs->next;
    //cannot pass in this node, must be root node
    //exe_commands(node, filefd, STDOUT_FILENO, envp);
    waitpid(childpid, NULL, 0);
    close (filefd);
    unlink("hd.txt");
    return (1);
}