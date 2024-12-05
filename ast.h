/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2024/12/05 17:51:57 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "tokenizer.h"

typedef enum e_node_type
{
    NODE_PIPE,
    NODE_COMMAND,
} t_node_type;

typedef struct s_redirection
{
    t_token_type    type;       // TOKEN_REDIR_IN, TOKEN_REDIR_OUT, etc.
    char            *file;      // Filename or delimiter for heredoc
    struct s_redirection *next; // Multiple redirections possible
} t_redirection;

typedef struct s_ast_node
{
    t_node_type      type;
    char            **args;         // Command and its args
    int             argc;
    t_redirection   *redirections;  // List of redirections for this command
    struct s_ast_node *left;
    struct s_ast_node *right;
} t_ast_node;


#endif