/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:19:11 by myuen             #+#    #+#             */
/*   Updated: 2025/02/15 19:31:30 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_whitespace_helper(const char *input, char *output, int *i,\
	int *j, int *in_space)
{
	if (ft_isspace(input[*i]))
	{
		if (!*in_space) 
		{
			output[*j] = ' ';
			*in_space = 1;
			(*j)++;
		}
	}
	else
	{
		output[*j] = input[*i];
		*in_space = 0;
		(*j)++;
	}
}

void	remove_whitespace(const char *input, char *output)
{
	int	i;
	int	j;
	int	in_space;
	
	i = 0;
	j = 0;
	in_space = 1;
	while (input[i])
	{
		remove_whitespace_helper(input, output, &i, &j, &in_space);
		i++;
	}
	if (j > 0 && output[j - 1] == ' ')
		j--;
	output[j] = '\0';
}

char	*word_split(const char *input)
{
	size_t	len;
	char	*result;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	result = malloc(len + 1);
	if (!result)
		return NULL;
	remove_whitespace(input, result);
	return (result);
}
