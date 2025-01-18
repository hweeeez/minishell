/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:23:16 by myuen             #+#    #+#             */
/*   Updated: 2025/01/18 17:35:33 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	ret = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (ret != NULL)
	{
		ft_strlcpy(ret, s1, ft_strlen(s1) + 1);
		ft_strlcat(ret, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	}
	return (ret);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	ret = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (ret != NULL)
	{
		ft_strlcpy(ret, s1, ft_strlen(s1) + 1);
		ft_strlcat(ret, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	}
	free(s1);
	free(s2);
	s1 = NULL;
	s2 = NULL;
	return (ret);
}
