/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:36:59 by myuen             #+#    #+#             */
/*   Updated: 2024/06/06 17:22:27 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				ret;
	int				sign;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	ret = 0;
	while (ft_isdigit(str[i]))
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return (ret * sign);
}
/*
   The string may begin with an arbitrary amount of white space (as
       determined by isspace(3)) followed by a single optional '+' or
       '-' sign.

       The remainder of the string is converted to a int value in the
       obvious manner, stopping at the first character which is not a
       valid digit in the given base.  (In bases above 10, the letter
       'A' in either uppercase or lowercase represents 10, 'B'
       represents 11, and so forth, with 'Z' representing 35.)

       If endptr is not NULL, strtol() stores the address of the first
       invalid character in *endptr.  If there were no digits at all,
       strtol() stores the original value of nptr in *endptr (and
       returns 0).  In particular, if *nptr is not '\0' but **endptr is
       '\0' on return, the entire string is valid.
   */
