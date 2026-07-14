#include "libft.h"

void	ft_putendl_fd(char *s)
{
	ft_putstr(s);
	write(STDOUT_FILENO, "\n", 1);
}
