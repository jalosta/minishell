#include "libft.h"

int	ft_putchar_fd(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}
