#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (dest == src && n == 0)
		return (dest);
	d = (char *)dest;
	s = (const char *)src;
	if (d > s)
	{
		while (n-- > 0)
			d[n] = s[n];
		return (dest);
	}
	else
		return (ft_memcpy(dest, src, n));
}
