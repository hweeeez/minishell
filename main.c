/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:45:38 by hui-lim           #+#    #+#             */
/*   Updated: 2024/12/16 21:20:44 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*temp test define and function*/
# define EXIT_CODE "exit"
static void print_tokens(t_token *tokens)
{
    t_token *current;
    
    current = tokens;
    while (current)
    {
        printf("Token: [%s], Type: ", current->value);
        if (current->type == TOKEN_WORD)
            printf("WORD\n");
        else if (current->type == TOKEN_PIPE)
            printf("PIPE\n");
        else if (current->type == TOKEN_REDIR_IN)
            printf("REDIR_IN\n");
        else if (current->type == TOKEN_REDIR_OUT)
            printf("REDIR_OUT\n");
        else if (current->type == TOKEN_HEREDOC)
            printf("HEREDOC\n");
        else if (current->type == TOKEN_APPEND)
            printf("APPEND\n");
        current = current->next;
    }
    printf("\n");
}
int	main(void)
{
    char	*s;
	t_token	*tok;

    if (setup_signals() == 1)
        return (1);
    while (1)
    {
        s = readline(PROMPT);
        if (!s)
        {
            rl_clear_history();
            return (0);
        }
        if (*s)
		    if (ft_strncmp(s, EXIT_CODE, sizeof(EXIT_CODE)) == 0)
            {
                free(s);
                rl_clear_history();
                return (0);
            }
            add_history(s);
			tok = tokenize(s);
            if (tok)
            {
                print_tokens(tok);
                free_token_list(tok);
            }
        free(s);
    }
}