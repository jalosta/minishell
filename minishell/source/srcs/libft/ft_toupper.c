#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - LOWER_TO_UPPER_CASE_DIFFERENCE);
	return (c);
}
