/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:11:40 by hui-lim           #+#    #+#             */
/*   Updated: 2025/02/02 20:53:08 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ispath(char *tok)
{
	if (tok[0] == '/' || (tok[0] == '.' && tok[1] == '/'))
		return (1);
	return (0);
}

void	makenewnode(t_node **newnode, t_node **tree, int type)
{
	(*newnode) = createnode();
	(*newnode)->type = type;
	addnode(tree, *newnode);
}

void	addarg(char ***args, int *nowords, char *add)
{
	copyarray(args, *nowords, add);
	(*nowords)++;
}

t_node	*createnode(void)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->left = NULL;
	node->right = NULL;
	node->type = NODE_PIPE;
	node->prev = NULL;
	node->rootredir = NULL;
	node->redirs = NULL;
	node->args = NULL;
	node->argc = 0;
	return (node);
}

int	parseword(t_node **newnode, t_shell ** shell, t_node **tree, char *tok)
{
	char		*word;
	static int	nowords;

	if ((*newnode) == NULL || (*newnode)->type == 0)
	{
		makenewnode(newnode, tree, NODE_COMMAND);
		nowords = 0;
	}
	if ((*newnode)->args == NULL)
	{
		if (isbuiltin(tok))
			word = ft_strdup(tok);
		else
			word = ft_find_cmd_path(tok, &((*newnode)->args), (*shell)->env);
		if (word != NULL && (*newnode)->args == NULL)
		{
			copyarray(&(*newnode)->args, nowords, word);
			free(word);
		}
		else if (word == NULL)
		{
			if (ispath(tok))
			{
				if (check_path_type(tok) == TYPE_DIR)
					print_parse_error(tok, "Is a directory", 126, shell);
				else if (check_path_type(tok) == TYPE_FILE)
				{
					if (access(tok, W_OK) == -1)
						print_parse_error(tok, "Permission denied", 126, shell);
				}
				else
					print_parse_error(tok, "No such file or directory", 127, shell);
			}
			else
				print_parse_error(tok, "Command not found", 127, shell);
			return (0);
		}
	}
	else
	{
		if (check_dir_exists(tok) == 0)
			return (0);
		copyarray(&(*newnode)->args, nowords, tok);
	}
	nowords++;
	return (1);
}

void	parseredir(t_node **newnode, t_node **tree, t_token **tok)
{
	if ((*newnode) == NULL)
		makenewnode(newnode, tree, 1);
	makeredir(newnode, tok);
}
