#include "minirt.h"

void	arg_check(int argc, char **argv)
{
	char	*period;

	if (argc != 2)
		error(1);
	period = ft_strchr(argv[1], '.');
	if (!period)
		error(2);
	if (ft_strncmp(period, ".rt", 4) != 0)
		error(2);
}

int	main(int argc, char **argv)
{
	arg_check(argc, argv);
	exit(EXIT_SUCCESS);
}