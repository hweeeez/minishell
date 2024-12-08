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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	s_len;
	size_t	d_len;
	size_t	i;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dest);
	if (size <= d_len)
		return (size + s_len);
	i = 0;
	while (src[i] && (d_len + i) < (size - 1))
	{
		dest[d_len + i] = src[i];
		i++;
	}
	dest[d_len + i] = '\0';
	return (d_len + s_len);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	size_t	len;

	if (s)
	{
		str = (char *) s;
		len = ft_strlen(s);
		if ((char)c == '\0')
			return (str + len);
		while (*str != '\0')
		{
			if (*str == (char)c)
				return (str);
			str++;
		}
	}
	return (NULL);
}

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

size_t	ft_strlen(const char* s)
{
	size_t	len;

	len = 0;
	while (*s++ != '\0')
		len++;
	return (len);
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

char	*ft_substr(char const *s, unsigned int start, size_t size)
{
	int		i;
	int		len;
	char	*dest;
	char	*src;

	len = (int)size;
	src = (char *)s;
	if (ft_strlen(src) - start < size)
		len = ft_strlen(src) - start;
	if (start > (unsigned int)ft_strlen(src))
		return (dest = ft_strdup("\0"));
	dest = malloc(len + 1);
	if (!dest)
		return (0);
	i = 0;
	while (i < len)
	{
		dest[i] = src[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
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

void	ft_free_split(char ***split)
{
	int	i;

	i = 0;
	if (*split)
	{
		while ((*split)[i])
		{
			free((*split)[i]);
			(*split)[i] = NULL;
			i++;
		}
		free(*split);
		*split = NULL;
	}
}
