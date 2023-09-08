#include "minirt.h"

void	test_atod(void);
void	test_arrlen(void);
void	test_isdouble(void);
void	test_isrgb(void);

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
	t_data	*file_data;

	arg_check(argc, argv);
	file_data = parse_file(argv[1]);
	test_parser(file_data);
	free_data(file_data);
	system("leaks test");
	exit(EXIT_SUCCESS);
}

// int	main(void)
// {
// 	// Main to test utils
// 	test_atod();
// 	test_arrlen();
// 	test_isdouble();
// 	test_isrgb();
// }