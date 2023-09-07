#include "minirt.h"

void	arg_check(int argc, char **argv)
{
	char	*period;

	if (argc != 2)
		arg_error(1);
	period = ft_strchr(argv[1], '.');
	if (!period)
		arg_error(2);
	if (ft_strncmp(period, ".rt", 4) != 0)
		arg_error(2);
}

int	main(int argc, char **argv)
{
	t_data	file_data;

	arg_check(argc, argv);
	parse_file(&file_data, argv[1]);
	free_data(&file_data);
	exit(EXIT_SUCCESS);
}