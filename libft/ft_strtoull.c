/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoull.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:52:20 by myuen             #+#    #+#             */
/*   Updated: 2024/10/02 19:41:20 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static const char	*ft_check_base(const char *str, int *base)
// {
// 	if (*base < 0 || *base > 36 || *base == 1)
// 	{
// 		*base = 0;
// 		return (str);
// 	}
// 	if (*base == 0 || *base == 16 || *base == 8)
// 	{
// 		if (*str == '0')
// 		{
// 			if (*(str + 1) == 'x' || *(str + 1) == 'X')
// 			{
// 				*base = 16;
// 				return (str + 2);
// 			}
// 			else
// 			{
// 				*base = 8;
// 				return (str + 1);
// 			}
// 		}
// 		else
// 			*base = 10;
// 	}
// 	return (str);
// }

// static int	ft_char_to_digit(char c, int base)
// {
// 	int	value;

// 	if (c >= '0' && c <= '9')
// 		value = c - '0';
// 	else if (c >= 'a' && c <= 'z')
// 		value = c - 'a' + 10;
// 	else if (c >= 'A' && c <= 'Z')
// 		value = c - 'A' + 10;
// 	else
// 		return (-1);
// 	if (value >= base)
// 		return (-1);
// 	return (value);
// }

// static int	ft_set_sign(const char **str)
// {
// 	int	sign;

// 	sign = 1;
// 	if (**str == '-' || **str == '+')
// 	{
// 		if (**str == '-')
// 			sign = -1;
// 		(*str)++;
// 	}
// 	return (sign);
// }

static unsigned long long	ft_parse_str(\
	const char **str, int base, int sign)
{
	unsigned long long	result;
	int					digit;

	result = 0;
	digit = ft_char_to_digit(**str, base);
	while (digit != -1)
	{
		(*str)++;
		if (result > (ULLONG_MAX - digit) / base)
		{
			if (sign == 1)
				return (ULLONG_MAX);
			else
				return (0);
		}
		result = result * base + digit;
		digit = ft_char_to_digit(**str, base);
	}
	return (result);
}

static unsigned long long	ft_handle_negative_sign(\
				unsigned long long result, int sign)
{
	if (sign == -1 && result != 0)
		return (~result + 1);
	return (result);
}

static unsigned long long	ft_handle_empty_str(\
				const char *str, char **endptr)
{
	if (endptr)
		*endptr = (char *)--str;
	return (0);
}

static unsigned long long	ft_handle_invalid_base(\
					const char *str, char **endptr)
{
	if (endptr)
		*endptr = (char *)str;
	return (0);
}

unsigned long long	ft_strtoull(\
	const char *str, char **endptr, int base)
{
	int					sign;
	unsigned long long	result;

	while (ft_isspace(*str))
		str++;
	sign = ft_set_sign(&str);
	if (*str == '\0')
		return (ft_handle_empty_str(str, endptr));
	str = ft_check_base(str, &base);
	if (base == 0)
		return (ft_handle_invalid_base(str, endptr));
	result = ft_parse_str(&str, base, sign);
	if (endptr)
		*endptr = (char *)str;
	return (ft_handle_negative_sign(result, sign));
}

/*Test

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "libft.h"

void test_strtoull(const char *str, int base) {
	char *endptr1, *endptr2;
	unsigned long long val1, val2;
	int errno1, errno2;

	errno = 0;
	val1 = strtoull(str, &endptr1, base);
	errno1 = errno;

	errno = 0;
	val2 = ft_strtoull(str, &endptr2, base);
	errno2 = errno;

	printf("Testing: \"%s\" (base %d)\n", str, base);
	printf("strtoull:    %llu (endptr: %ld, errno: %d)\n",\
	val1, endptr1 - str, errno1);
	printf("ft_strtoull: %llu (endptr: %ld, errno: %d)\n",\
	val2, endptr2 - str, errno2);
	printf("Match: %s\n\n", (val1 == val2 &&\
	endptr1 == endptr2 && errno1 == errno2) ? "Yes" : "No");
}

int main() {
	// Basic test cases
	test_strtoull("123", 10);
	test_strtoull("+123abc", 10);
	test_strtoull("0x1A", 0);
	test_strtoull("0777", 0);
	test_strtoull("  +0xFF", 16);
	
	// Negative numbers (will be treated as large positive numbers)
	test_strtoull("-123", 10);
	test_strtoull("  -0xFF", 16);

	// Overflow test cases
	printf("--- Overflow Test Cases ---\n");
	test_strtoull("18446744073709551615", 10);  // ULLONG_MAX
	test_strtoull("18446744073709551616", 10);  // ULLONG_MAX + 1
	test_strtoull("18446744073709551617", 10);  // ULLONG_MAX + 2
	test_strtoull("28446744073709551615", 10);  // larger than ULLONG_MAX
	
	// Base-specific overflow cases
	printf("--- Base-specific Overflow Test Cases ---\n");
	test_strtoull("FFFFFFFFFFFFFFFF", 16);  // ULLONG_MAX in hex
	test_strtoull("10000000000000000", 16); // ULLONG_MAX + 1 in hex
	test_strtoull("FFFFFFFFFFFFFFFF1", 16); // Overflow in hex
	
	// Edge cases
	printf("--- Edge Cases ---\n");
	test_strtoull("18446744073709551614", 10);  // ULLONG_MAX - 1
	test_strtoull("18446744073709551615", 10);  // ULLONG_MAX
	test_strtoull("18446744073709551616", 10);  // ULLONG_MAX + 1
	test_strtoull("-1", 10);                    // Should be ULLONG_MAX
	test_strtoull("-18446744073709551615", 10); // Large negative

	return 0;
}
*/
