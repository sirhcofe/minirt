/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 01:56:27 by jthor             #+#    #+#             */
/*   Updated: 2023/08/31 01:56:36 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_header(char *str)
{
	size_t	strlen = ft_strlen(str);

	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_putstr_fd("#****", STDOUT_FILENO);
	for (size_t	i = 0; i < strlen; i++)
		ft_putchar_fd('*', STDOUT_FILENO);
	ft_putendl_fd("****#", STDOUT_FILENO);
	ft_putchar_fd('#', STDOUT_FILENO);
	for (size_t i = 0; i < (strlen + 8); i++)
		ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putchar_fd('#', STDOUT_FILENO);
	ft_putstr_fd("\n#    ", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putendl_fd("    #", STDOUT_FILENO);
	ft_putchar_fd('#', STDOUT_FILENO);
	for (size_t i = 0; i < (strlen + 8); i++)
		ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putchar_fd('#', STDOUT_FILENO);
	ft_putstr_fd("\n#****", STDOUT_FILENO);
	for (size_t	i = 0; i < strlen; i++)
		ft_putchar_fd('*', STDOUT_FILENO);
	ft_putendl_fd("****#", STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	print_colour(t_rgb obj)
{
	printf("Colour = %u, %u, %u\n", obj.red, obj.green, obj.blue);
}

void	print_point(t_coord obj, int flag)
{
	if (flag == 1)
		printf("Point  = (%f, %f, %f, %f)\n", obj.x, obj.y, obj.z, obj.w);
	else
		printf("Vector = (%f, %f, %f, %f)\n", obj.x, obj.y, obj.z, obj.w);

}

void	print_ambience(t_amb obj)
{
	if (obj.flag == 0) {
		printf("No ambience object found!\n");
		return ;
	}
	else if (obj.flag == -1) {
		printf("Error expected for ambience object!\n");
		return ;
	}
	printf("Flag   = %d\n", obj.flag);
	printf("Ratio  = %f\n", obj.ratio);
	print_colour(obj.colour);
}

void	print_camera(t_cam obj)
{
	if (obj.flag == 0) {
		printf("No camera object found!\n");
		return ;
	}
	else if (obj.flag == -1) {
		printf("Error expected for camera object!\n");
		return ;
	}
	printf("Flag   = %d\n", obj.flag);
	print_point(obj.point, 1);
	print_point(obj.orient_vector, 2);
	printf("POV    = %f\n", obj.fov);
}

void	print_light(t_light obj)
{
	if (obj.flag == 0) {
		printf("No light object found!\n");
		return ;
	}
	else if (obj.flag == -1) {
		printf("Error expected for light object!\n");
		return ;
	}
	printf("Flag   = %d\n", obj.flag);
	print_point(obj.point, 1);
	printf("Ratio  = %f\n", obj.ratio);
	print_colour(obj.colour);
}

void	print_spheres(t_sp *obj)
{
	static int	count = 1;

	if (obj->flag == -1) {
		printf("Expected error on sphere no. %d\n", count);
	}
	printf("===================================\n");
	print_point(obj->center, 1);
	printf("2r     = %f\n", obj->dia);
	print_colour(obj->colour);
	printf("===================================\n");
	count++;
}

void	print_planes(t_pl *obj)
{
	static int	count = 1;

	if (obj->flag == -1) {
		printf("Expected error on plane no. %d\n", count);
	}
	printf("===================================\n");
	print_point(obj->point, 1);
	print_point(obj->normal_vector, 0);
	print_colour(obj->colour);
	printf("===================================\n");
	count++;
}

void	print_cylinders(t_cy *obj)
{
	static int	count = 1;

	if (obj->flag == -1) {
		printf("Expected error on plane no. %d\n", count);
	}
	printf("===================================\n");
	print_point(obj->center, 1);
	print_point(obj->axis_vector, 0);
	printf("2r     = %f\n", obj->dia);
	printf("Height = %f\n", obj->height);
	print_colour(obj->colour);
	printf("===================================\n");
	count++;
}

void	print_shape(int type, int num, t_list *lst)
{
	if (num == 0 && lst == NULL) {
		printf("No objects found!\n");
		return ;
	}
	else if (num == 0) {
		printf("No objects but list is initialised!\n");
		return ;
	}
	else if (lst == NULL) {
		printf("Object(s) found but list is not initialised!\n");
		return ;
	}
	if (num != ft_lstsize(lst)) {
		printf("Number of objects does not correspond with list length!\n");
	}
	printf("Count  = %d\n", num);
	if (type == 0)
		ft_lstiter(lst, (void *)print_spheres);
	else if (type == 1)
		ft_lstiter(lst, (void *)print_planes);
	else
		ft_lstiter(lst, (void *)print_cylinders);
}

void	test_parser(t_data *f_data)
{
	print_header("Starting parsing tests");
	// Ambience
	print_header("Checking ambience object");
	print_ambience(f_data->ambience);
	// Camera
	print_header("Checking camera object");
	print_camera(f_data->camera);
	// Light
	print_header("Checking light object");
	print_light(f_data->light);
	// Sphere
	print_header("Checking sphere objects");
	print_shape(0, f_data->num_sp, f_data->spheres);
	// Planes
	print_header("Checking plane objects");
	print_shape(1, f_data->num_pl, f_data->planes);
	// Cylinders
	print_header("Checking cylinder objects");
	print_shape(2, f_data->num_cy, f_data->cylinders);
}
