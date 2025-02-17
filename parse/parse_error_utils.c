
#include"minishell.h"

void    print_parse_error(char *cmd, char *error, int status, t_shell **shell)
{
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd(error, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    (*shell)->exit_status = status;
}

int	ispath(char *tok)
{
	if (tok[0] == '/')
		return (1);
	if ((tok[0] == '.' && tok[1] == '/'))
		return (2);
	return (0);
}

int    handle_path(char *tok, t_shell **shell)
{
    int path_type;

    path_type = ispath(tok);
    if (path_type != 0)
    {
        if (check_path_type(tok) == TYPE_DIR)
            return (print_parse_error(tok, "Is a directory", 126, shell), -1);
        else if (check_path_type(tok) == TYPE_FILE)
        {
            if ((path_type == 2 && access(tok, X_OK) == -1) || (path_type == 1 && access(tok, W_OK) == -1))
            return (print_parse_error(tok, "Permission denied", 126, shell), -1);
        }
        else
            return (print_parse_error(tok, "No such file or directory", 127, shell), -1);
        return (1);
    }
    return (0);
}