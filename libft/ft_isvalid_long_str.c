/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalid_long_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:42:35 by myuen             #+#    #+#             */
/*   Updated: 2024/10/03 15:43:51 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isvalid_long_str(const char *str, int base)
{
	char		*endptr;
	long long	result;

	if (str && str[0])
	{
		result = ft_strtoll(str, &endptr, base);
		if (endptr == NULL || *endptr != '\0' || str == endptr)
			return (0);
		if (result > (long long) LONG_MAX || result < (long long) LONG_MIN)
			return (0);
		return (1);
	}
	else
		return (0);
}
