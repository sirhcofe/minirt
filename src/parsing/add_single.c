#include "minirt.h"

int	add_ambience(t_amb *obj , char **arr)
{
	if (obj->flag == 1)
		return (3);
	if (ft_strncmp(arr[0], "A", 2) != 0 || ft_arrlen(arr) != 3)
		return (2);
	obj->ratio = assign_ratio(&(obj->flag), arr[1]);
	assign_rgb(&(obj->flag), &(obj->colour), arr[2]);
	if (obj->flag == -1)
		return (2);
	obj->flag = 1;
	return (0);
}

int	add_camera(t_cam *obj, char **arr)
{
	if (obj->flag == 1)
		return (3);
	if (ft_strncmp(arr[0], "C", 2) != 0 || ft_arrlen(arr) != 4)
		return (2);
	assign_coord(&(obj->flag), &(obj->point), arr[1]);
	assign_vector(&(obj->flag), &(obj->orient_vector), arr[2]);
	obj->fov = assign_fov(&(obj->flag), arr[3]);
	if (obj->flag == -1)
		return (2);
	obj->flag = 1;
	return (0);
}

int	add_light(t_light *obj, char **arr)
{
	if (obj->flag == 1)
		return (3);
	if (ft_strncmp(arr[0], "L", 2) != 0 || ft_arrlen(arr) != 4)
		return (2);
	assign_coord(&(obj->flag), &(obj->point), arr[1]);
	obj->ratio = assign_ratio(&(obj->flag), arr[2]);
	assign_rgb(&(obj->flag), &(obj->colour), arr[3]);
	if (obj->flag == -1)
		return (2);
	obj->flag = 1;
	return (0);
}