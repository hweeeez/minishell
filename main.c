/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:45:38 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/30 21:33:01 by myuen            ###   ########.fr       */
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

static int	handle_exit_command(char *input)
{
	if (*input && ft_strncmp(input, EXIT_CMD, sizeof(EXIT_CMD)) == 0)
	{
		ft_putstr_fd("exit\n", 2);
		return (1);
	}
	return (0);
}

static void	processtree(t_token	*token, t_shell	*shell, t_sigacts	**sigs)
{
	t_node	*tree;
	t_node	*root;

	if (token->value[0] == '$')
		return ;
	tree = createnode();
	root = tree;
	inittree(&tree, token, shell->env);
	tree = root;
	if (execute(tree, shell->env) == 2)
	{
		if (ft_heredoc(tree, shell->env) > 0)
		{
			sigaction(SIGINT, &(*sigs)->sa, NULL);
			rl_event_hook = NULL;
		}
	}
	freetree(&tree);
}

/*Edit this function to add more features when minishell is run*/
static int	process_input(char *input, t_token **tok, t_shell **shell, t_sigacts **sigs)
{
	if (tokenize(input, tok, *shell))
		return (1);
	if (*tok)
		print_tokens(*tok);
	processtree(*tok, *shell, sigs);
	return (0);
}

static int	ms_exit(char *input, t_token **tok, t_shell **shell, t_sigacts **sig)
{
	int	exit_status;

	exit_status = (*shell)->exit_status;
	free(input);
	input = NULL;
	rl_clear_history();
	free_token_list(tok);
	cleanup_shell(shell);
	free(*sig);
	return (exit_status);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_shell		*shell;
	t_token		*token;
	t_sigacts	*sigs;

	(void)argc;
	(void)argv;
	token = NULL;
	input = NULL;
	shell = init_shell(env);
	if (!shell)
		return (ms_exit(input, &token, &shell, &sigs));
	if (setup_signals(&sigs) == 1)
		return (ms_exit(input, &token, &shell, &sigs));
	while (1)
	{
		input = readline(PROMPT);
		if (handle_empty_input(input))
			return (ms_exit(input, &token, &shell, &sigs));
		if (handle_exit_command(input))
			return (ms_exit(input, &token, &shell, &sigs));
		add_history(input);
		process_input(input, &token, &shell, &sigs);
		free(input);
		//free_token_list(&token);
	}
}
