#include "minirt.h"

void arg_check(int argc, char **argv)
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
	t_minirt	rt;
	t_data		file_data;

	arg_check(argc, argv);
	init_mlx_window(&rt);
	parse_file(&file_data, argv[1]);
	free_data(&file_data);
	// exit(EXIT_SUCCESS);
}
