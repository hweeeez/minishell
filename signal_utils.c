#include "minishell.h"

static void quitchild(int sig)
{
	exit(0);
}

void    init_exesigs(t_sigs** sigs)
{
    (*sigs) = (t_sigs*)malloc(sizeof(t_sigs));
    (*sigs)->ignore.sa_handler = SIG_IGN;
    sigemptyset(&((*sigs)->ignore).sa_mask);
	(*sigs)->ignore.sa_flags = 0;
    (*sigs)->sigint.sa_handler = quitchild;
    sigemptyset(&((*sigs)->sigint).sa_mask);
	(*sigs)->sigint.sa_flags = 0;
}

void    do_sigaction(int sig1, int sig2, t_sigs* sigs)
{
    if (sig1 == SIGQUIT)
        sigaction(SIGQUIT, &(sigs->quit), NULL);
    if (sig2 == SIGINT)
        sigaction(SIGINT, &(sigs->sigint), NULL);
}