#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	dup[len] = '\0';
	while (len-- > 0)
		dup[len] = s[len];
	return (dup);
}
