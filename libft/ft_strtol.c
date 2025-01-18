/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:52:20 by myuen             #+#    #+#             */
/*   Updated: 2024/10/02 19:41:20 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*ft_check_base(const char *str, int *base)
{
	if (*base < 0 || *base > 36 || *base == 1)
	{
		*base = 0;
		return (str);
	}
	if (*base == 0 || *base == 16 || *base == 8)
	{
		if (*str == '0')
		{
			if (*(str + 1) == 'x' || *(str + 1) == 'X')
			{
				*base = 16;
				return (str + 2);
			}
			else
			{
				*base = 8;
				return (str + 1);
			}
		}
		else
			*base = 10;
	}
	return (str);
}

static int	ft_char_to_digit(char c, int base)
{
	int	value;

	if (c >= '0' && c <= '9')
		value = c - '0';
	else if (c >= 'a' && c <= 'z')
		value = c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z')
		value = c - 'A' + 10;
	else
		return (-1);
	if (value >= base)
		return (-1);
	return (value);
}

static int	ft_set_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

long	ft_parse_str(const char **str, int base, int sign)
{
	long	result;
	int		digit;

	result = 0;
	digit = ft_char_to_digit(**str, base);
	while (digit != -1)
	{
		(*str)++;
		if (result > (LONG_MAX - digit) / base)
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		result = result * base + digit;
		digit = ft_char_to_digit(**str, base);
	}
	if (result == LONG_MAX && sign == -1)
		return (0);
	return (result * sign);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	int		sign;
	long	result;

	while (ft_isspace(*str))
		str++;
	sign = ft_set_sign(&str);
	if (*str == '\0')
	{
		if (endptr)
			*endptr = (char *)--str;
		return (0);
	}
	str = ft_check_base(str, &base);
	if (base == 0)
	{
		if (endptr)
			*endptr = (char *) str;
		return (0);
	}
	result = ft_parse_str(&str, base, sign);
	if (endptr)
		*endptr = (char *)str;
	return (result);
}

/*Test

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "libft.h"

void test_strtol(const char *str, int base) {
    char *endptr1, *endptr2;
    long val1, val2;
    int errno1, errno2;

    errno = 0;
    val1 = strtol(str, &endptr1, base);
    errno1 = errno;

    errno = 0;
    val2 = ft_strtol(str, &endptr2, base);
    errno2 = errno;

    printf("Testing: \"%s\" (base %d)\n", str, base);
    printf("strtol:    %ld (endptr: %ld, errno: %d)\n",\
	val1, endptr1 - str, errno1);
    printf("ft_strtol: %ld (endptr: %ld, errno: %d)\n",\
	val2, endptr2 - str, errno2);
    printf("Match: %s\n\n", (val1 == val2 &&
	\ endptr1 == endptr2 && errno1 == errno2) ? "Yes" : "No");
}

int main() {
    // Previous test cases
    test_strtol("123", 10);
    test_strtol("-123", 10);
    test_strtol("  +123abc", 10);
    test_strtol("0x1A", 0);
    test_strtol("0777", 0);
    test_strtol("  -0xFF", 16);

    // Overflow test cases
    printf("--- Overflow Test Cases ---\n");
    test_strtol("9223372036854775807", 10);  // LONG_MAX
    test_strtol("9223372036854775808", 10);  // LONG_MAX + 1
    test_strtol("9223372036854775809", 10);  // LONG_MAX + 2
    test_strtol("19223372036854775807", 10); // larger than LONG_MAX
    test_strtol("-9223372036854775808", 10); // LONG_MIN
    test_strtol("-9223372036854775809", 10); // LONG_MIN - 1
    test_strtol("-9223372036854775810", 10); // LONG_MIN - 2
    test_strtol("-19223372036854775808", 10); //smaller than LONG_MIN

    // Base-specific overflow cases
    printf("--- Base-specific Overflow Test Cases ---\n");
    test_strtol("7FFFFFFFFFFFFFFF", 16);  // LONG_MAX in hex
    test_strtol("8000000000000000", 16);  // LONG_MIN in hex
    test_strtol("7FFFFFFFFFFFFFFF1", 16); // Overflow in hex
    test_strtol("111111111111111111111111111111111111\
	1111111111111111111111111111", 2);  // LONG_MAX in binary
    test_strtol("111111111111111111111111111111111111\
	1111111111111111111111111112", 2);  // Overflow in binary

    // Edge cases
    printf("--- Edge Cases ---\n");
    test_strtol("9223372036854775806", 10);  // LONG_MAX - 1
    test_strtol("9223372036854775807", 10);  // LONG_MAX
    test_strtol("9223372036854775808", 10);  // LONG_MAX + 1
    test_strtol("-9223372036854775807", 10); // LONG_MIN + 1
    test_strtol("-9223372036854775808", 10); // LONG_MIN
    test_strtol("-9223372036854775809", 10); // LONG_MIN - 1

    return 0;
}
*/
