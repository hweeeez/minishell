/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:31:04 by myuen             #+#    #+#             */
/*   Updated: 2024/06/22 17:57:59 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (ft_strlen(little) == 0)
		return ((char *) big);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] && i + j < len)
		{
			j++;
			if (little[j] == '\0')
				return ((char *) big + i);
		}
		i++;
	}
	return (NULL);
}
/*
   The strnstr() function locates the first occurrence
   of the null-terminated string little in
     the string big, where not more than len
     characters are searched.  Characters that appear
     after a ‘\0’ character are not searched.
     If little is an empty string, big is returned;
     if little occurs nowhere in big, NULL is
     returned; otherwise a pointer to the first
     character of the first occurrence of little is
     returned.

   */
