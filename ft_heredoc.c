#include "minishell.h"

int received_sigint = 0;

void    exit_hd(int sig)
{
    received_sigint = 1;
}

int ft_heredoc(t_node *node, char **envp)
{
    pid_t   childpid;
    char    *s;
    int     filefd;
    t_redir  *redirs;
	struct	sigaction quit;
	struct	sigaction sig_int;

    // if SIGINT exit without executing, if EOF, print eof error msg then execute
    sig_int.sa_handler = exit_hd;
    sigaction(SIGINT, &sig_int, NULL);
    redirs = node->left->rootredir;
    filefd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    while (1)
    {
        s = readline("> ");
        if (s != NULL)
        {
            if (ft_strcmp(s, redirs->file) == 1 || received_sigint == 1)
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
    filefd = open(HEREDOC_FILE, O_RDONLY, 0644);
    redirs = redirs->next;
    exe_commands(node, filefd, STDOUT_FILENO, envp);
    waitpid(childpid, NULL, 0);
    close (filefd);
    unlink(HEREDOC_FILE);
    return (1);
}