#include "minirt.h"

void	error(int status)
{
	if (status == 1)
		ft_putstr_fd("Usage: ./miniRT <MAP FILE>\n", 2);
	if (status == 2)
		ft_putstr_fd("Invalid map file.\n", 2);
	exit(EXIT_FAILURE);
}