#include "minishell.h"
#include "tokenizer.h"

void	inittree(t_tree* tree, t_token* tokens)
{
	t_token *current;
	t_redir	temp_redir;

	(*tree)->pipe = (t_pipe *)malloc(sizeof(t_pipe));
	current = tokens;
	while (current)
	{
		parsetoken(current);
		int fd = access(current->value, R_OK & & X_OK);
		if (fd > -1)
			
		current = current->next;
	}
}

void	parsetoken(t_token* token, t_tree* tree)
{
	t_redir*	redir;
	
	if (token->type == 2 || token->type == 3) // < or >
	{
		//create redir
		redir = (t_redir*)malloc(sizeof(t_redir));
		redir.type = (*token)->type;
		redir.value = (*token)->next->value;
		*token = (*token)->next->next;
	}
	if (token->type == 1) // |
	{
		//create redir
		redir = (t_redir*)malloc(sizeof(t_redir));
		redir.type = (*token)->type;
		redir.value = (*token)->next->value;
		*token = (*token)->next->next;
	}
}

void	addnode()
{

}
