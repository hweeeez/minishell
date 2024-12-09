/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:17:23 by myuen             #+#    #+#             */
/*   Updated: 2024/05/31 19:22:18 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	size_t	len;

	if (s)
	{
		str = (char *) s;
		len = ft_strlen(s);
		if ((char)c == '\0')
			return (str + len);
		while (*str != '\0')
		{
			if (*str == (char)c)
				return (str);
			str++;
		}
	}
	return (NULL);
}
//actual strchr segfault when null parameter is sent