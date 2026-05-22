#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	uc;

	str = (unsigned char *)s;
	uc = (unsigned char)c;
	while (n-- > 0)
	{
		if (*str == uc)
			return ((void *)str);
		str++;
	}
	return (NULL);
}
