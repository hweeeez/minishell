/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:12:08 by myuen             #+#    #+#             */
/*   Updated: 2024/06/12 19:59:05 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*ret;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	if (s1[start] == '\0')
		return (ft_strdup(""));
	while (ft_strchr(set, (int) s1[start]))
		start++;
	end = ft_strlen(s1) - 1 ;
	while (end > start && ft_strchr(set, (int) s1[end]))
		end--;
	ret = ft_substr(s1, start, end - start + 1);
	return (ret);
}
