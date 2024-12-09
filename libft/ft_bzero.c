/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:53:23 by myuen             #+#    #+#             */
/*   Updated: 2024/05/22 19:10:55 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_copy_block(void **dst_ptr, long c, size_t n)
{
	unsigned long	*ptr;

	ptr = (unsigned long *)*dst_ptr;
	*dst_ptr += n * sizeof(long);
	while (n--)
		*ptr++ = c;
}

static void	ft_copy_chip(void **dst_ptr, char c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)*dst_ptr;
	*dst_ptr += n * sizeof(char);
	while (n--)
		*ptr++ = c;
}

void	ft_bzero(void *s, size_t n)
{
	unsigned int	block;
	unsigned int	chip;

	if (n < 1)
		return ;
	block = n / sizeof(long);
	chip = n % sizeof(long);
	if (block)
		ft_copy_block(&s, 0, block);
	ft_copy_chip(&s, 0, chip);
}

/*
direct implementation
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
	return ;
}
*/
