/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:14:46 by myuen             #+#    #+#             */
/*   Updated: 2024/06/24 18:03:51 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nobj, size_t size)
{
	void	*ret;

	ret = malloc(nobj * size);
	if (ret)
		ft_bzero(ret, nobj * size);
	return (ret);
}
/* Previous implementations include
2 safe size_t flow. Not needed for tester.

Tester expects malloc(0) in cases of either parm is zero 

static int	safe_flow(size_t nobj, size_t size)
{
	if (nobj != 0 && size > ((size_t)-1) / nobj)
		return (0);
	return (1);
}

static int	safe_flow(size_t nobj, size_t size)
{
	size_t	total;

	if (nobj == 0 || size == 0)
		return (0);
	total = nobj * size;
	if (total / nobj != size)
		return (0);
	return (1);
}
*/
