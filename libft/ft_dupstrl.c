/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dupstrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:43:42 by myuen             #+#    #+#             */
/*   Updated: 2025/02/01 18:44:59 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**dupstrl(char **str)
{
	char	**new_str_array;
	size_t	i;
	size_t	size;

	size = 0;
	while (str[size])
		size++;
	new_str_array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_str_array)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_str_array[i] = ft_strdup(str[i]);
		if (!new_str_array[i])
		{
			freestrl(new_str_array);
			return (NULL);
		}
		i++;
	}
	new_str_array[i] = NULL;
	return (new_str_array);
}
