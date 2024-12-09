/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:00:07 by myuen             #+#    #+#             */
/*   Updated: 2024/06/19 19:15:33 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	size_t	len;
	size_t	i;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (ret)
	{
		i = 0;
		while (i < len)
		{
			ret[i] = f(i, s[i]);
			i++;
		}
		ret[len] = '\0';
	}
	return (ret);
}
