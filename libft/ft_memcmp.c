/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:25:49 by myuen             #+#    #+#             */
/*   Updated: 2024/06/22 20:01:23 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *) s1;
	str2 = (const unsigned char *) s2;
	while (n--)
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		str1++;
		str2++;
	}
	return (0);
}
/*
   The memcmp() function returns an
   integer less than, equal to, or
       greater than zero if the first
	   n bytes of s1 is found,
       respectively, to be less than,
	   to match, or be greater than the
       first n bytes of s2.

       For a nonzero return value,
	   the sign is determined by the sign of
       the difference between the
	   first pair of bytes (interpreted as
       unsigned char) that differ in s1 and s2.

       If n is zero, the return value is zero.
*/
