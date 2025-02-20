/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:56:24 by myuen             #+#    #+#             */
/*   Updated: 2025/02/03 15:55:22 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exit(t_shell **shell, char **args)
{
	int exit_code;
	//int is_interactive;

	exit_code = (*shell)->exit_status;
	//is_interactive = isatty(STDIN_FILENO);
	//printf(">> Entering ft_exit\n");
	if (!shell || !*shell)
	{
		//printf(">> Error: shell is NULL\n");
		exit(1);
	}
	//printf(">> Current exit_status: %d\n", exit_code);
	// Only print exit message if in interactive mode
	//if (is_interactive)
	// Handle case with no args or just the command name
	if (!args || !args[0])
	{
		//printf(">> args is NULL or empty, exiting with status: %d\n", exit_code);
		rl_clear_history();
		//printf(">> History cleared\n");
		cleanup_shell(shell);
		*shell = NULL;
		//printf(">> Shell cleanup done\n");
		ft_putstr_fd("exit\n", 1);
		exit(exit_code);
	}
	// If no argument after command name
	if (args[0] && !args[1])
	{
		//printf(">> No exit code provided, exiting with status: %d\n", exit_code);
		rl_clear_history();
		//printf(">> History cleared\n");
		cleanup_shell(shell);
		*shell = NULL;
		//printf(">> Shell cleanup done\n");
		ft_putstr_fd("exit\n", 1);
		exit(exit_code);
	}
	// Print args for debugging
	//int i = 0;
	// while (args[i])
	// {
	// 	printf(">> args[%d]: '%s'\n", i, args[i]);
	// 	i++;
	// }
	if (!ft_isvalid_integer_str(args[1], 10))
	{
		//printf(">> Invalid integer: '%s'\n", args[1]);
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		rl_clear_history();
		//printf(">> History cleared\n");
		cleanup_shell(shell);
		*shell = NULL;
		//printf(">> Shell cleanup done\n");
		ft_putstr_fd("exit\n", 1);
		exit(2);
	}
	if (args[2])
	{
		//printf(">> Too many arguments\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_code = ft_atoi(args[1]) % 256;
	//printf(">> Exit code calculated: %d (from: %s)\n", exit_code, args[1]);
	//printf(">> Exiting with code: %d\n", exit_code);
	rl_clear_history();
	//printf(">> History cleared\n");
	cleanup_shell(shell);
	//printf(">> Shell cleanup done\n");
	*shell = NULL;
	ft_putstr_fd("exit\n", 1);
	exit(exit_code);
}

// int ft_exit(t_shell **shell, char **args)
// {
//     int exit_code;

//     printf(">> Entering ft_exit\n");

//     if (!shell || !*shell)
//     {
//         printf(">> Error: shell is NULL\n");
//         exit(1);
//     }

//     printf(">> Current exit_status: %d\n", (*shell)->exit_status);
	
//     rl_clear_history();
//     printf(">> History cleared\n");

//     cleanup_shell(shell);
//     printf(">> Shell cleanup done\n");

//     // First check if args is NULL
//     if (!args)
//     {
//         printf(">> args is NULL, exiting with status: %d\n", (*shell)->exit_status);
//         ft_putstr_fd("exit\n", 1);
//         exit((*shell)->exit_status);
//     }

//     // Now we can safely check args array
//     if (!args[0] || !args[1])
//     {
//         printf(">> No exit code provided, exiting with status: %d\n", 
//             (*shell)->exit_status);
//         ft_putstr_fd("exit\n", 1);
//         exit((*shell)->exit_status);
//     }

//     // Print args for debugging
//     int i = 0;
//     while (args[i])
//     {
//         printf(">> args[%d]: '%s'\n", i, args[i]);
//         i++;
//     }

//     if (!ft_isvalid_integer_str(args[1], 10))
//     {
//         printf(">> Invalid integer: '%s'\n", args[1]);
//         ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
//         ft_putstr_fd("exit\n", 1);
//         exit(2);
//     }

//     if (args[2])
//     {
//         printf(">> Too many arguments\n");
//         ft_putstr_fd("minishell: exit: too many arguments\n", 2);
//         return (1);
//     }

//     exit_code = ft_atoi(args[1]) % 256;
//     printf(">> Exit code calculated: %d (from: %s)\n", exit_code, args[1]);
	
//     ft_putstr_fd("exit\n", 1);
//     printf(">> Exiting with code: %d\n", exit_code);
//     exit(exit_code);
// }

// int	ft_exit(t_shell **shell, char **args)
// {
// 	int	exit_code;

// 	rl_clear_history();
// 	cleanup_shell(shell);
// 	if (!args || !args[1])
// 		exit((*shell)->exit_status);
// 	if (!ft_isvalid_integer_str(args[1], 10))
// 	{
// 		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
// 		exit(2);
// 	}
// 	if (args[2])
// 	{
// 		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
// 		return (1);
// 	}
// 	exit_code = ft_atoi(args[1]) % 256;
// 	ft_putstr_fd("exit\n", 1);
// 	exit(exit_code);
// }
