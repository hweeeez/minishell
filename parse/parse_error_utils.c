
#include"minishell.h"

void    print_parse_error(char *cmd, char *error, int status, t_shell **shell)
{
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd(error, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    (*shell)->exit_status = status;
}