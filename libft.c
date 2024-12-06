/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:19:26 by myuen             #+#    #+#             */
/*   Updated: 2024/12/04 19:28:03 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	ft_copy_block(void** dst, const void** src, size_t n)
{
	unsigned long* d_ptr;
	const unsigned long* s_ptr;

	d_ptr = (unsigned long*)*dst;
	s_ptr = (const unsigned long*)*src;
	*dst += n * sizeof(long);
	*src += n * sizeof(long);
	while (n--)
		*d_ptr++ = *s_ptr++;
}

static void	ft_copy_chip(void** dst, const void** src, size_t n)
{
	unsigned char* d_ptr;
	const unsigned char* s_ptr;

	d_ptr = (unsigned char*)*dst;
	s_ptr = (const unsigned char*)*src;
	*dst += n * sizeof(char);
	*src += n * sizeof(char);
	while (n--)
		*d_ptr++ = *s_ptr++;
}

void* ft_memcpy(void* dest, const void* src, size_t n)
{
	void* ret;
	unsigned int	block;
	unsigned int	chip;

	if (n == 0 || dest == src)
		return (dest);
	ret = dest;
	block = n / sizeof(long);
	chip = n % sizeof(long);
	if (block)
		ft_copy_block(&dest, &src, block);
	ft_copy_chip(&dest, &src, chip);
	return (ret);
}

size_t	ft_strlen(const char* s)
{
	size_t	len;

	len = 0;
	while (*s++ != '\0')
		len++;
	return (len);
}

size_t	ft_strlcpy(char* dest, const char* src, size_t size)
{
	size_t	len;
	size_t	ret;

	ret = ft_strlen(src);
	if (size > 0)
	{
		if (ret >= size)
			len = size - 1;
		else
			len = ret;
		ft_memcpy(dest, src, len);
		dest[len] = '\0';
	}
	return (ret);
}

char* ft_strdup(const char* s)
{
	unsigned int	len;
	char* ret;

	len = ft_strlen(s);
	ret = (char*)malloc((len + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, s, len + 1);
	return (ret);
}

static int	count_substr(const char* s, const char c)
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

static char* extract_substr(char** pos, const char c)
{
	char* start;

	if (!(*pos))
		return (NULL);
	while (**pos == c)
		(*pos)++;
	start = *pos;
	while ((**pos) != c && (**pos) != '\0')
		(*pos)++;
	return (ft_substr(start, 0, *pos - start));
}

static void	free_str(char** s, unsigned int count)
{
	while (count > 0)
	{
		free(s[--count]);
		s[count] = NULL;
	}
	free(s);
}

char** ft_split(char const* s, char c)
{
	char** ret;
	char* read_pos;
	unsigned int	substr_total;
	unsigned int	substr_index;

	substr_total = count_substr(s, c);
	ret = (char**)malloc((substr_total + 1) * sizeof(char*));
	if (ret)
	{
		read_pos = (char*)s;
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