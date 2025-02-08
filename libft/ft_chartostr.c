/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chartostr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:36:06 by myuen             #+#    #+#             */
/*   Updated: 2025/01/16 21:11:08 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_chartostr(char c)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}
