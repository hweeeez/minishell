/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:45:38 by hui-lim           #+#    #+#             */
/*   Updated: 2024/12/18 21:58:27 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*temp test define and function*/
#define EXIT_CMD "exit"

static void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("[%s], Type: ", current->value);
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

/*helper functions*/
static int	handle_empty_input(char *input)
{
	if (!input)
	{
		rl_clear_history();
		return (1);
	}
	return (0);
}

static int	handle_exit_command(char *input)
{
	if (*input && ft_strncmp(input, EXIT_CMD, sizeof(EXIT_CMD)) == 0)
	{
		ft_putstr_fd("exit\n", 2);
		free(input);
		rl_clear_history();
		return (1);
	}
	return (0);
}

/*Edit this function to add more features when minishell is run*/
static void	process_input(char *input, t_token **token)
{
	*token = tokenize(input);
	if (*token)
		print_tokens(*token);
	free_token_list(*token);
}

int	main(void)
{
	char	*input;
	t_token	*token;

	if (setup_signals() == 1)
		return (1);
	while (1)
	{
		input = readline(PROMPT);
		if (handle_empty_input(input))
			return (0);
		if (handle_exit_command(input))
			return (0);
		add_history(input);
		process_input(input, &token);
		free(input);
	}
}
