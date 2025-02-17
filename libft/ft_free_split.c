/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:43:21 by myuen             #+#    #+#             */
/*   Updated: 2025/02/01 18:45:12 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **str_array)
{
	size_t	i;

	if (str_array)
	{
		i = 0;
		while (str_array[i])
			free(str_array[i++]);
		free(str_array);
	}
}
