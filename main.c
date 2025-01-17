/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:45:38 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/17 21:39:37 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*temp test define and function*/
#define EXIT_CMD "exit"

static void	print_tokens(t_token *token_list)
{
	t_token	*current;
	int		i;

	i = 1;
	current = token_list;
	printf("%10s\n", "Token(s)");
	while (current)
	{
		printf("%-2d[%s], Type: ", i++, current->value);
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
		else
			printf("UNEXPECTED\n");
		current = current->next;
	}
	printf("%10s\n", "--End of List--");
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

static int	handle_exit_command(char *input, t_token *tok, t_shell *shell)
{
	if (*input && ft_strncmp(input, EXIT_CMD, sizeof(EXIT_CMD)) == 0)
	{
		ft_putstr_fd("exit\n", 2);
		free(input);
		rl_clear_history();
		free_token_list(tok);
		cleanup_shell(shell);
		return (1);
	}
	return (0);
}

/*Edit this function to add more features when minishell is run*/
static int	process_input(char *input, t_token **tok, t_shell *shell)
{
	if (tokenize(input, tok, shell))
	{
		free_token_list(*tok);
		return (1);
	}
	if (*tok)
		print_tokens(*tok);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_shell	*shell;
	t_token	*token;

	(void)argc;
	(void)argv;
	token = NULL;
	shell = init_shell(env);
	if (!shell)
		return (1);
	if (setup_signals() == 1)
		return (1);
	while (1)
	{
		input = readline(PROMPT);
		if (handle_empty_input(input))
			return (0);
		if (handle_exit_command(input, token, shell))
			return (0);
		add_history(input);
		if (process_input(input, &token, shell))
			printf("Error - token fail");
		free(input);
	}
}
