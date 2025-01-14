#include "minishell.h"

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