/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:05:41 by myuen             #+#    #+#             */
/*   Updated: 2024/06/22 19:48:50 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	val;

	if (s)
	{
		val = (unsigned char) c;
		str = (unsigned char *) s;
		while (n--)
		{
			if ((unsigned char)*str == val)
				return ((void *) str);
			str++;
		}
	}
	return (NULL);
}
//actual memchr segfault when null parameter is sent