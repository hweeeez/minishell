/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitany.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:37:15 by myuen             #+#    #+#             */
/*   Updated: 2025/02/17 16:27:47 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_delim(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

static int	count_substr(const char *s, const char *delim)
{
	int	count;
	int	in_str;

	count = 0;
	in_str = 0;
	if (s)
	{
		while (*s)
		{
			if (is_delim(*s, delim))
				in_str = 0;
			else if (!in_str)
			{
				in_str = 1;
				count++;
			}
			s++;
		}
	}
	return (count);
}

static char	*extract_substr(char **pos, const char *delim)
{
	char	*start;

	if (!(*pos))
		return (NULL);
	while (is_delim(**pos, delim))
		(*pos)++;
	start = *pos;
	while (**pos && !is_delim(**pos, delim))
		(*pos)++;
	return (ft_substr(start, 0, *pos - start));
}

static void	free_str(char **s, unsigned int count)
{
	while (count > 0)
	{
		free(s[--count]);
		s[count] = NULL;
	}
	free(s);
}

char	**ft_splitany(const char *s, const char *delim)
{
	char			**ret;
	char			*read_pos;
	unsigned int	substr_total;
	unsigned int	substr_index;

	substr_total = count_substr(s, delim);
	ret = (char **)malloc((substr_total + 1) * sizeof(char *));
	if (ret)
	{
		read_pos = (char *)s;
		substr_index = 0;
		while (substr_index < substr_total)
		{
			ret[substr_index] = extract_substr(&read_pos, delim);
			if (!ret[substr_index])
			{
				free_str(ret, substr_index);
				return (NULL);
			}
			substr_index++;
		}
		ret[substr_index] = NULL;
	}
	return (ret);
}
