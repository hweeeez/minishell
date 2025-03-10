/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:45:38 by hui-lim           #+#    #+#             */
/*   Updated: 2025/02/03 18:26:01 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_empty_input(char *input)
{
	if (!input)
	{
		rl_clear_history();
		return (1);
	}
	return (0);
}

static void	processtree(t_token	*token, t_shell	**shell, struct sigaction *sigs)
{
	(*shell)->tree = createnode();
	(*shell)->root = (*shell)->tree;
	if (inittree(&(*shell)->tree, token, shell) == 0)
	{
		freetree(&(*shell)->root);
		return ;
	}
	(*shell)->tree = (*shell)->root;
	execute((*shell)->tree, shell);
	setup_signals(sigs);
	freetree(&(*shell)->root);
}

static int	minishell_loop(char *input, t_token **tok, \
				t_shell **shell, struct sigaction *sigs)
{
	int	status;

	while (1)
	{
		input = readline(PROMPT);
		if (handle_empty_input(input))
			ft_exit(shell, NULL, NULL);
		if (input[0] != '\0')
			add_history(input);
		if (g_received_sigint == 1)
		{
			(*shell)->exit_status = 130;
			g_received_sigint = 0;
		}
		status = 0;
		status = tokenize(input, tok, *shell);
		free(input);
		if (status)
		{
			(*shell)->exit_status = status;
			continue ;
		}
		processtree(*tok, shell, sigs);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char				*input;
	t_shell				*shell;
	struct sigaction	sigint;

	(void)argc;
	(void)argv;
	input = NULL;
	shell = init_shell(env);
	if (!shell)
		exit(1);
	if (setup_signals(&sigint) == 1)
		return (ft_exit(&shell, NULL, NULL));
	return (minishell_loop(input, &(shell->token), &shell, &sigint));
}

/*
static void	print_tokens(t_token *token_list)
{
	t_token	*current;
	int		i;

	i = 1;
	current = token_list;
	printf("%10s\n", "Token(s)");
	while (current)
	{
		printf("%-2d[%s] | Type: ", i++, current->value);
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
}*/
/*
static int	handle_exit_command(char *input)
{
	if (*input && ft_strncmp(input, EXIT_CMD, sizeof(EXIT_CMD)) == 0)
	{
		// ft_putstr_fd("exit\n", 2);
		return (1);
	}
	return (0);
}*/

/*
static void	processtree(t_token	*token, t_shell	**shell, struct sigaction *sigs)
{
	//t_node	*tree;
	//t_node	*root;

	(*shell)->tree = createnode();
	(*shell)->root = (*shell)->tree;
	if (inittree(&(*shell)->tree, token, shell) == 0)
	{
		//tree = root;
		freetree(&(*shell)->root);
		return ;
	}
	(*shell)->tree = (*shell)->root;
	if (execute((*shell)->tree, shell) == 2)
	{
		// if (ft_heredoc(tree, shell) > 0)
		// {
		// 	sigaction(SIGINT, sigs, NULL);
		// 	rl_event_hook = NULL;
		// }
	}
	//(*shell)->hasprinted = 0;
	//(*shell)->skipnl = 0;
	setup_signals(sigs);
	freetree(&(*shell)->root);
}*/
/*
static int	minishell_loop(char *input, t_token **tok, 
			t_shell **shell, struct sigaction *sigs)
{
	while (1)
	{
		input = readline(PROMPT);
		if (handle_empty_input(input))
			ft_exit(shell, NULL, NULL) ;
			// return (ft_exit(shell, NULL));
		// if (handle_exit_command(input))
		// 	return (ft_exit(shell, NULL));
		add_history(input);
		if (tokenize(input, tok, *shell))
		{
			free(input);
			continue ;
		}
		free(input);
		// print_tokens(*tok);
		processtree(*tok, shell, sigs);
	}
	return (0);
}*/
