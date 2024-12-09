/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:23:53 by myuen             #+#    #+#             */
/*   Updated: 2024/05/23 18:49:39 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	s_len;
	size_t	d_len;
	size_t	i;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dest);
	if (size <= d_len)
		return (size + s_len);
	i = 0;
	while (src[i] && (d_len + i) < (size - 1))
	{
		dest[d_len + i] = src[i];
		i++;
	}
	dest[d_len + i] = '\0';
	return (d_len + s_len);
}
/*===========================================
Appends the null-terminated string src 
to the end of the null-terminated string dst, 
but with the following additional checks:

1. append at most size - strlen(dst) - 1 bytes from src to dst,
size is the total size of the destination buffer and 
strlen(dst) is the length of the current content in dst.

2. It ensures that the resulting string is null-terminated.

If strlcat successfully concatenates the strings without truncating, 
it returns the total length of the resulting string. 

If the resulting string is truncated to fit within the size limit, 
it will return the sum of the lengths of the two input strings.

1. Does strlcat always null-terminate dst?
dst will be null-terminated by strlcat if strlcat modifies dst. 
Strlcat does not modify dst if dst is already fully occupied. 
dst is considered fully-occupied if no NUL is found in 
the first size - 1 bytes of dst (or if size is 0).

So there are two cases in which dst will not be null-terminated by strlcat. 
One is that dst is a null-terminated string of exactly size - 1 bytes, 
in which case it is not modified and continues to be null-terminated. 

The second case is that dst was not null-terminated initially, 
and in that case it will still be unterminated after the call to strlcat.

2. How is the length of the original destination string measured?
size is expected to be the size of the memory region containing dst, 
so that dst[size] is assumed to be an invalid memory reference. 
Consequently, if dst starts out as a valid (and therefore null-terminated)
string, its length will be strictly less than size and 
strlcat will use strlen(dst)as its length. 
If dst is not valid, then its size is assumed to be size for the 
purposes of the return value. In this case, dst will not be modified. 
See above.
*/
