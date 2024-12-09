/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:04:17 by myuen             #+#    #+#             */
/*   Updated: 2024/06/19 18:29:07 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int	ret;

	if (n == 0)
		return (1);
	ret = 0;
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		n /= 10;
		ret++;
	}
	return (ret);
}

static int	check_negative(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

char	*ft_itoa(int n)
{
	int		neg;
	int		len;
	char	*ret;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	neg = check_negative(n);
	if (neg)
		n = -n;
	len = ft_count(n);
	ret = (char *)malloc((len + 1 + neg) * sizeof(char));
	if (ret)
	{
		ret[len + neg] = '\0';
		while (len > 0)
		{
			ret[--len + neg] = (n % 10) + '0';
			n /= 10;
		}
		if (neg)
			ret[0] = '-';
	}
	return (ret);
}
