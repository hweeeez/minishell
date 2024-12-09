/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:28:09 by myuen             #+#    #+#             */
/*   Updated: 2024/09/28 16:17:43 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <stddef.h>

/*=======================================
		IS functions - 11
========================================*/
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isblank(int c);
int		ft_isspace(int c);
int		ft_isodd(int n);
int		ft_iseven(int n);
int		ft_iswithin(long long n, long long l, long long h);
int		ft_isvalid_integer_str(const char *str, int base);
/*======================================
		Strings functions - 14
=======================================*/
size_t	ft_strlcat(char	*dest, const char *src, size_t size);
size_t	ft_strlcpy(char	*dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
/*====================================
		Memory functions - 7
=====================================*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nobj, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
/*===================================
		Translate functions - 5
=====================================*/
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *str);
int		ft_abs(int num);
char	*ft_itoa(int n);
long	ft_strtol(const char *str, char **endptr, int base);
/*=====================================
		I/O functions -4
=======================================*/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/*======================================
	Macros - NOT IMPLIMENTED - NORM ERROR 

# define IS_ODD(num) ((num) & 1)
# define IS_EVEN(num) (!(IS_ODD(num)))
# define IS_BETWEEN(n,L,H) (((n) >= (L) && (n) <= (H)))
# define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
# define COMPARE(x,y) (((x) > (y)) - ((x) < (y)))
# define SIGN(x) COMPARE(x,0)
=======================================*/
#endif
