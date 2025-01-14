/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:11:40 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/14 21:11:42 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    makenewnode(t_node **newnode, t_node **tree, int type)
{
    if ((*newnode) == NULL)
    {
        (*newnode) = createnode();
        (*newnode)->type = type;
        addnode(tree, newnode);
    }
}

void makeredir(t_node **newnode, t_node* tree, t_token **token)
{
 	t_redir *redir;

    redir = (t_redir*)malloc(sizeof(t_redir));
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

void    addarg(char ***args, int *nowords, char *add, t_node **node)
{
    copyarray(&args, nowords, add);
    (*node)->args = args;
    nowords++;
}
