/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:33:09 by myuen             #+#    #+#             */
/*   Updated: 2024/06/12 18:15:03 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;
	size_t	ret;

	ret = ft_strlen(src);
	if (size > 0)
	{
		if (ret >= size)
			len = size - 1;
		else
			len = ret;
		ft_memcpy(dest, src, len);
		dest[len] = '\0';
	}
	return (ret);
}
/*can be optimised - strlcpy copy up to (size - 1) char from the
  NUL-terminated str src to dest, NUL-terminating the result.
Q- waht if source and destination points to the same object???*/
