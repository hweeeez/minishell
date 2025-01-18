/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:10:21 by myuen             #+#    #+#             */
/*   Updated: 2024/05/31 20:29:07 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_copy_block(void **dst, const void **src, size_t n)
{
	unsigned long		*d_ptr;
	const unsigned long	*s_ptr;

	d_ptr = (unsigned long *)*dst;
	s_ptr = (const unsigned long *)*src;
	*dst += n * sizeof(long);
	*src += n * sizeof(long);
	while (n--)
		*d_ptr++ = *s_ptr++;
}

static void	ft_copy_chip(void **dst, const void **src, size_t n)
{
	unsigned char		*d_ptr;
	const unsigned char	*s_ptr;

	d_ptr = (unsigned char *)*dst;
	s_ptr = (const unsigned char *)*src;
	*dst += n * sizeof(char);
	*src += n * sizeof(char);
	while (n--)
		*d_ptr++ = *s_ptr++;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void			*ret;
	unsigned int	block;
	unsigned int	chip;

	if (n == 0 || dest == src)
		return (dest);
	ret = dest;
	block = n / sizeof(long);
	chip = n % sizeof (long);
	if (block)
		ft_copy_block(&dest, &src, block);
	ft_copy_chip(&dest, &src, chip);
	return (ret);
}

/* direct implementation
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (n == 0 || dest == src)
		return (dest);
	d = (char *) dest;
	s = (const char *) src;
	while (n--)
		*d++ = *s++;
	return (dest);
}
*/
