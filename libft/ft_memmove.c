/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:00:12 by myuen             #+#    #+#             */
/*   Updated: 2024/05/24 19:45:57 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (n == 0 || dest == src)
		return (dest);
	d = (char *) dest;
	s = (const char *) src;
	if (dest <= src)
		while (n--)
			*d++ = *s++;
	else if (dest > src)
	{
		d += n - 1;
		s += n - 1;
		while (n--)
			*d-- = *s--;
	}
	return (dest);
}
/*not sure if need to check dest or src == 0*/
