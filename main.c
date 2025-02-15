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

/*temp test define and function*/
#define EXIT_CMD "exit"

// static void	print_tokens(t_token *token_list)
// {
// 	t_token	*current;
// 	int		i;

// 	i = 1;
// 	current = token_list;
// 	printf("%10s\n", "Token(s)");
// 	while (current)
// 	{
// 		printf("%-2d[%s], Type: ", i++, current->value);
// 		if (current->type == TOKEN_WORD)
// 			printf("WORD\n");
// 		else if (current->type == TOKEN_PIPE)
// 			printf("PIPE\n");
// 		else if (current->type == TOKEN_REDIR_IN)
// 			printf("REDIR_IN\n");
// 		else if (current->type == TOKEN_REDIR_OUT)
// 			printf("REDIR_OUT\n");
// 		else if (current->type == TOKEN_HEREDOC)
// 			printf("HEREDOC\n");
// 		else if (current->type == TOKEN_APPEND)
// 			printf("APPEND\n");
// 		else
// 			printf("UNEXPECTED\n");
// 		current = current->next;
// 	}
// 	printf("%10s\n", "--End of List--");
// }

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
		return (1);
	}
	return (0);
}

static int	ms_exit(char *input, t_token **tok, t_shell **shell)
{
	int	exit_status;

	exit_status = (*shell)->exit_status;
	free(input);
	input = NULL;
	rl_clear_history();
	free_token_list(tok);
	cleanup_shell(shell);
	return (exit_status);
}

static void	processtree(t_token	*token, t_shell	**shell, struct sigaction *sigs)
{
	t_node	*tree;
	t_node	*root;

	tree = createnode();
	root = tree;
	if (inittree(&tree, token, shell) == 0)
	{
		//tree = root;
		freetree(&root);
		return ;
	}
	tree = root;
	if (execute(tree, shell) == 2)
	{
		if (ft_heredoc(tree, shell) > 0)
		{
			sigaction(SIGINT, sigs, NULL);
			rl_event_hook = NULL;
		}
	}
	(*shell)->hasprinted = 0;
	setup_signals(sigs);
	freetree(&tree);
}

/*Edit this function to add more features when minishell is run*/
static int	minishell_loop(char *input, t_token **tok, t_shell **shell, struct sigaction *sigs)
{
	while (1)
	{
		input = readline(PROMPT);
		if (handle_empty_input(input))
			return (ms_exit(input, tok, shell));
		if (handle_exit_command(input))//need to be replaced
			return (ms_exit(input, tok, shell));
		add_history(input);
		if (tokenize(input, tok, *shell))
		{
			free(input);
			continue ;
		}
		processtree(*tok, shell, sigs);
		free(input);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_shell		*shell;
	t_token		*token;
	struct sigaction	sigint;

	(void)argc;
	(void)argv;
	token = NULL;
	input = NULL;
	shell = init_shell(env);
	if (!shell)
		return (ms_exit(input, &token, &shell));
	if (setup_signals(&sigint) == 1)
		return (ms_exit(input, &token, &shell));
	return (minishell_loop(input, &token, &shell, &sigint));
}
