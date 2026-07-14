#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		len;
	
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len + 1);
	return (dup);
}
