/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:04:21 by myuen             #+#    #+#             */
/*   Updated: 2024/12/16 21:07:10 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_signal(int sig)
{
    (void) sig;
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}

int     setup_signals(void)
{
    struct sigaction sa;
    struct sigaction quit;

    ft_memset(&sa, 0, sizeof(sa));
    ft_memset(&quit, 0, sizeof(quit));
    quit.sa_handler = SIG_IGN;
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGQUIT, &quit, NULL) == -1)
        return (1);
    if (sigaction(SIGINT, &sa, NULL) == -1)
        return (1);
    return (0);
}
