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

static void	getword(char **word, char *tok, t_node **new, t_shell **shell)
{
	if (isbuiltin(tok))
		*word = ft_strdup(tok);
	else
		*word = ft_find_cmd_path(tok, &((*new)->args), (*shell)->env);
}

static int	handle_word(char **word, int *no, t_node **new, char *tok)
{
	if (*word != NULL && (*new)->args == NULL)
		return (copyarray(&(*new)->args, *no, *word), free(*word), (*no)++, 1);
	else if (*word == NULL)
	{
		if (handle_path(tok) == -1)
			return (0);
		else if (handle_path(tok) == 0)
			print_parse_error(tok, "command not found");
	}
	else if (*word != NULL && (*new)->args != NULL)
		return ((*no)++, 1);
	return (-1);
}

int	parseword(t_node **new, t_shell **shell, t_node **tree, char *tok)
{
	char		*word;
	static int	no;
	int			handleword;

	word = NULL;
	handleword = 0;
	if ((*new) == NULL || (*new)->type == 0)
	{
		makenewnode(new, tree, NODE_COMMAND);
		no = 0;
	}
	if ((*new)->args == NULL)
	{
		getword(&word, tok, new, shell);
		handleword = handle_word(&word, &no, new, tok);
		if (handleword != -1)
			return (handleword);
	}
	else if (check_dir_exists(tok) == 0)
		return (0);
	return (copyarray(&(*new)->args, no, tok), no++, 1);
}

void	parseredir(t_node **newnode, t_node **tree, t_token **tok)
{
	if ((*newnode) == NULL)
		makenewnode(newnode, tree, 1);
	makeredir(newnode, tok);
}
