#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + LOWER_TO_UPPER_CASE_DIFFERENCE);
	return (c);
}
