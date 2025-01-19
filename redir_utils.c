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

int	isredir(int type)
{
	if (type == TOKEN_REDIR_IN)
		return (1);
	if (type == TOKEN_REDIR_OUT)
		return (1);
	if (type == TOKEN_APPEND)
		return (1);
	if (type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

void	makeredir(t_node **newnode, t_token **token)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	redir->type = (*token)->type;
	redir->file = (*token)->next->value;
	redir->next = NULL;
	if ((*newnode)->redirs == NULL)
	{
		(*newnode)->redirs = redir;
		(*newnode)->rootredir = redir;
	}
	else
	{	
		(*newnode)->redirs->next = redir;
		(*newnode)->redirs = (*newnode)->redirs->next;
	}
	(*token) = (*token)->next;
}
