/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isallwhitespace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:51:26 by myuen             #+#    #+#             */
/*   Updated: 2024/10/11 16:52:57 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isallwhitespace(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isspace((unsigned char) *str))
			return (0);
		str++;
	}
	return (1);
}
