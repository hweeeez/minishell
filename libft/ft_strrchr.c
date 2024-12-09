/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:37:15 by myuen             #+#    #+#             */
/*   Updated: 2024/06/22 18:02:38 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	len;

	if (s)
	{
		len = ft_strlen(s);
		str = (char *) s;
		if ((char) c == '\0')
			return (str + len);
		while (len > 0)
		{
			if (str[len - 1] == (char) c)
				return (&str[len - 1]);
			len--;
		}
	}
	return (NULL);
}
//actual strrchr segfault when null parameter is sent