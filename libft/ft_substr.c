/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:11:11 by myuen             #+#    #+#             */
/*   Updated: 2024/06/12 18:41:02 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	str_len;

	str_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= str_len)
		len = 0;
	else if (len > str_len - start)
		len = str_len - start;
	ret = (char *) malloc((len + 1) * sizeof(char));
	if (ret)
	{
		i = 0;
		while (i < len)
		{
			ret[i] = s[start + i];
			i++;
		}
		ret[i] = '\0';
	}
	return (ret);
}
