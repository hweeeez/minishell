/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:37:15 by myuen             #+#    #+#             */
/*   Updated: 2025/02/17 20:10:34 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	has_delim(const char *str, const char *delim)
// {
// 	while (*delim)
// 	{
// 		if (ft_strchr(str, *delim))
// 			return (1);
// 		delim++;
// 	}
// 	return (0);
// }
static int	is_delim(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next_token = NULL;
	char		*token_start;

	if(!delim)
		return (NULL);
	if (str != NULL)
		next_token = str;
	if (next_token == NULL)
		return (NULL);
	while (*next_token && is_delim(*next_token, delim))
		next_token++;
	if (*next_token == '\0')
		return (NULL);
	token_start = next_token;
	while (*next_token && !is_delim(*next_token, delim))
		next_token++;
	if (*next_token)
	{
		*next_token = '\0';
		next_token++;
	}
	else
		next_token = NULL;
	return (ft_strdup(token_start));
}
/*
int main() {
	char str[] = "  Hello,  World! 42  is awesome!  ";
	char *token;
	
	printf("Tokens:\n");
	
	// First call with the string
	token = ft_strtok(str, " ,!");
	while (token != NULL) {
		printf("[%s]\n", token);
		token = ft_strtok(NULL, " ,!"); // Subsequent calls with NULL
	}

	return 0;
}*/