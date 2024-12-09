/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalid_integer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:42:35 by myuen             #+#    #+#             */
/*   Updated: 2024/10/03 15:43:51 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_isvalid_integer(const char *str, int base)
{
	char	*endptr;
	long	result;

	if (str)
	{
		result = ft_strtol(str, &endptr, base);
		if (*endptr != '\0')
			return (0);
		if (result > INT_MAX || result < INT_MIN)
			return (0);
		return (1);
	}
	else
		return (0);
}
