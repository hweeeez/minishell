/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:33:21 by myuen             #+#    #+#             */
/*   Updated: 2025/01/16 20:58:31 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, unsigned int n)
{
	char	*ret;

	ret = (char *)malloc((n + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, s, n + 1);
	return (ret);
}
