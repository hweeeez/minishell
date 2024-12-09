/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:47:11 by myuen             #+#    #+#             */
/*   Updated: 2024/06/22 17:43:56 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_substr(const char *s, const char c)
{
	int	count;
	int	in_str;

	count = 0;
	in_str = 0;
	if (s)
	{
		while (*s)
		{
			if (*s == c)
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

static char	*extract_substr(char **pos, const char c)
{
	char	*start;

	if (!(*pos))
		return (NULL);
	while (**pos == c)
		(*pos)++;
	start = *pos;
	while ((**pos) != c && (**pos) != '\0')
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

char	**ft_split(char const *s, char c)
{
	char			**ret;
	char			*read_pos;
	unsigned int	substr_total;
	unsigned int	substr_index;

	substr_total = count_substr(s, c);
	ret = (char **)malloc((substr_total + 1) * sizeof (char *));
	if (ret)
	{
		read_pos = (char *) s;
		substr_index = 0;
		while (substr_index < substr_total)
		{
			ret[substr_index] = extract_substr(&read_pos, c);
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
/*
static int	count_substr(const char *s, const char c)
{
	int	count;
	int	in_str;

	count = 0;
	in_str = 0;
	if (s)
	{
		while (*s)
		{
			if (*s == c)
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

static char	*extract_substr(char const *s, const char c, unsigned int i)
{
	unsigned int	start;
	unsigned int	end;

	if (!s)
		return (NULL);
	while (*s == c)
		s++;
	start = 0;
	while (i > 0)
	{
		if (s[start] == c)
		{
			i--;
			while (s[start] == c)
				start++;
		}
		else
			start++;
	}
	end = start;
	while (s[end] && s[end] != c)
		end++;
	return (ft_substr(s, start, end - start));
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

char	**ft_split(char const *s, char c)
{
	char			**ret;
	unsigned int	substr_total;
	unsigned int	substr_index;

	substr_total = count_substr(s, c);
	ret = (char **)malloc((substr_total + 1) * sizeof (char *));
	if (ret)
	{
		substr_index = 0;
		while (substr_index < substr_total)
		{
			ret[substr_index] = extract_substr(s, c, substr_index);
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
*/