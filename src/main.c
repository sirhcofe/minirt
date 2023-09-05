#include "minirt.h"

void arg_check(int argc, char **argv)
{
	char	*period;

	if (argc != 2)
		error("Usage: ./miniRT <MAP FILE>\n");
	period = ft_strchr(argv[1], '.');
	if (!period)
		error("Invalid map file.\n");
	if (ft_strncmp(period, ".rt", 4) != 0)
		error("Invalid map file.\n");
}

int	main(int argc, char **argv)
{
	t_minirt	rt;
	t_data		file_data;

	arg_check(argc, argv);
	init_mlx_window(&rt);
	set_controls(&file_data, &rt);
	// parse_file(&file_data, argv[1]);
	// free_data(&file_data);
	// exit(EXIT_SUCCESS);
	mlx_loop(rt.mlx);
}
