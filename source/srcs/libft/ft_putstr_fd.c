#include "libft.h"

int	ft_putstr_fd(const char *s, int fd)
{
	int	count;
	int	e_check;

	count = 0;
	if (s == NULL)
		return (ft_putstr_fd("(null)", fd));
	while (*s != '\0')
	{
		e_check = ft_putchar_fd(*s, fd);
		if (e_check == WRITE_FAIL)
			return (WRITE_FAIL);
		count += e_check;
		s++;
	}
	return (count);
}
