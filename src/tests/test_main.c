#include "minirt.h"

void	test_atod(void);
void	test_arrlen(void);
void	test_isdouble(void);
void	test_isrgb(void);

void	arg_check(int argc, char **argv)
{
	char	*period;

	if (argc != 2)
		arg_error("Bad arguments\n");
	period = ft_strchr(argv[1], '.');
	if (!period)
		arg_error("Bad file\n");
	if (ft_strncmp(period, ".rt", 4) != 0)
		arg_error("Bad file\n");
}

void	add_intsct(void *node)
{
	t_object	*obj;

	obj = (t_object *)node;
	if (obj->e_idx == pl)
		*(obj->obj.plane.intsct) = (t_coord){10.0, 0.0, 0.0, 0.0};
	else if (obj->e_idx == sp)
		obj->obj.plane.intsct->x = 20.0;
	else if (obj->e_idx == cy)
		obj->obj.plane.intsct->x = 30.0;
	else
		printf("ERROR\n");
}

void	free_fdata(void *temp)
{
	t_object	*temp2;

	temp2 = (t_object *)temp;
	if (temp2->e_idx == pl)
		free(temp2->obj.plane.intsct);
	else if (temp2->e_idx == sp)
		free(temp2->obj.sphere.intsct);
	else
		free(temp2->obj.cylinder.intsct);
	free(temp2);
}

int	main(int argc, char **argv)
{
	t_data	*file_data;

	arg_check(argc, argv);
	file_data = parse_file(argv[1]);
	// ft_lstiter(file_data->objects, add_intsct);
	test_parser(file_data);
	ft_lstclear(&(file_data->objects), free_fdata);
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