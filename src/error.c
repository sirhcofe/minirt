#include "minirt.h"

void	error(int status)
{
	if (status == 1)
		ft_putstr_fd("Usage: ./miniRT <MAP FILE>\n", 2);
	if (status == 2)
		ft_putstr_fd("Invalid map file.\n", 2);
	exit(EXIT_FAILURE);
}

void	error_free(int status, t_data *f_data, char *gnl)
{
	ft_putstr_fd("Error\n", 2);
	if (status == 1)
		ft_putstr_fd("Problematic object found in file\n", 2);
	else if (status == 2)
		ft_putstr_fd("Unrecognised object description\n", 2);
	else if (status == 3)
		ft_putstr_fd("More than one Camera, Light or Ambience object\n", 2);
	free_data(f_data);
	if (gnl)
		free(gnl);
	exit (EXIT_FAILURE);
}