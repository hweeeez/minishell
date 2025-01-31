#include "libft.h"

char	*ft_strcpy(char *src, int size)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(sizeof(size + 1));
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}