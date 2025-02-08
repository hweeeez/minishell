/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:19:26 by myuen             #+#    #+#             */
/*   Updated: 2025/01/30 17:54:48 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++ != '\0')
		len++;
	return (len);
}
/*
DESCRIPTION         
    The strlen() function calculates the length of the string pointed
    to by s, excluding the terminating null byte ('\0').
RETURN VALUE
    The strlen() function returns the number of bytes in the string
    pointed to by s.
*/