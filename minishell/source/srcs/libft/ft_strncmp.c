#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- > 0)
	{
		if (*s1 < *s2)
			return (NEGATIVE);
		else if (*s1 > *s2)
			return (POSITIVE);
		s1++;
		s2++;
	}
	return (EQUAL);
}
