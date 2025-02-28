/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strto_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:52:20 by myuen             #+#    #+#             */
/*   Updated: 2024/10/02 19:41:20 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_check_base(const char *str, int *base)
{
	if (*base < 0 || *base > 36 || *base == 1)
	{
		*base = 0;
		return (str);
	}
	if (*base == 0 || *base == 16 || *base == 8)
	{
		if (*str == '0')
		{
			if (*(str + 1) == 'x' || *(str + 1) == 'X')
			{
				*base = 16;
				return (str + 2);
			}
			else
			{
				*base = 8;
				return (str + 1);
			}
		}
		else
			*base = 10;
	}
	return (str);
}

int	ft_char_to_digit(char c, int base)
{
	int	value;

	if (c >= '0' && c <= '9')
		value = c - '0';
	else if (c >= 'a' && c <= 'z')
		value = c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z')
		value = c - 'A' + 10;
	else
		return (-1);
	if (value >= base)
		return (-1);
	return (value);
}

int	ft_set_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}
