/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:28:09 by myuen             #+#    #+#             */
/*   Updated: 2025/02/01 18:45:37 by myuen            ###   ########.fr       */
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
		IS functions - 14
========================================*/
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isblank(int c);
int					ft_isspace(int c);
int					ft_isodd(int n);
int					ft_iseven(int n);
int					ft_iswithin(long long n, long long l, long long h);
int					ft_isvalid_integer_str(const char *str, int base);
int					ft_isvalid_long_str(const char *str, int base);
int					ft_isallwhitespace(const char *str);
int					ft_isnowhitespace(const char *str);
/*------------------------------------
		Helpers
-------------------------------------*/
const char			*ft_check_base(const char *str, int *base);
int					ft_char_to_digit(char c, int base);
int					ft_set_sign(const char **str);
/*======================================
		Strings functions - 17
=======================================*/
size_t				ft_strlcat(char	*dest, const char *src, size_t size);
size_t				ft_strlcpy(char	*dest, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strnstr(const char *big, const char *little, \
					size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strdup(const char *s);
char				*ft_strndup(const char *s, unsigned int n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_free(char *s1, char *s2);
char				*ft_strtrim(char const *s1, char const *set);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
int					ft_strcmp(char *str1, char *str2);
char				*ft_strcpy(char *src, int size);
/*======================================
		String Array functions - 5
=======================================*/
char				*ft_strtok(char *str, const char *delim);
char				**ft_split(char const *s, char c);
char				**ft_splitany(const char *s, const char *delim);
char				**dup_split(char **str);
void				free_split(char **str_array);
/*====================================
		Memory functions - 7
=====================================*/
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nobj, size_t size);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
/*===================================
		Translate functions - 9
=====================================*/
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_atoi(const char *str);
int					ft_abs(int num);
char				*ft_itoa(int n);
long				ft_strtol(const char *str, char **endptr, int base);
long long			ft_strtoll(const char *str, char **endptr, int base);
unsigned long long	ft_strtoull(const char *str, char **endptr, int base);
char				*ft_chartostr(char c);
/*=====================================
		I/O functions -4
=======================================*/
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

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
