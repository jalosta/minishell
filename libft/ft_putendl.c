#include "libft.h"

void	ft_putendl(char *s)
{
	ft_putstr(s);
	write(STDOUT_FILENO, "\n", 1);
}
