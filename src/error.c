#include "minirt.h"

void	arg_error(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}

void	error_free(int status, t_data *f_data)
{
	ft_putstr_fd("Error\n", 2);
	if (status == 1)
		ft_putstr_fd("Problematic object found in file\n", 2);
	else if (status == 2)
		ft_putstr_fd("Unrecognised object description\n", 2);
	else if (status == 3)
		ft_putstr_fd("More than one Camera, Light or Ambience object\n", 2);
	free_data(f_data);
	exit (EXIT_FAILURE);
}