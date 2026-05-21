#include "libft.h"

static size_t	count_slices(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

static void	*free_double_string(char **strs, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
		free(strs[i++]);
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	size_t	slice_len;

	strs = malloc((count_slices(s, c) + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != '\0')
		{
			slice_len = ft_strlen(s);
			if (ft_strchr(s, c) != NULL)
				slice_len = ft_strchr(s, c) - s;
			strs[i++] = ft_substr(s, 0, slice_len);
			if (strs[i - 1] == NULL)
				return (free_double_string(strs, i - 1));
			s += slice_len;
		}
	}
	strs[i] = NULL;
	return (strs);
}
