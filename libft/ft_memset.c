/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:31:47 by myuen             #+#    #+#             */
/*   Updated: 2024/05/24 19:45:57 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*p;

	if (s)
	{
		p = (char *) s;
		while (n--)
			*p++ = (char) c;
	}
	return (s);
}
//actual memset segfault when null parameter is sent