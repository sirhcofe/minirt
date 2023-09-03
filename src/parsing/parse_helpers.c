#include "minirt.h"

double	assign_ratio(int *flag, char *str)
{
	double	conv_ratio;

	if (ft_isdouble(str) == 0)
		*flag = -1;
	conv_ratio = ft_atod(str);
	if (conv_ratio < 0.0 || conv_ratio > 1.0)
		*flag = -1;
	return (conv_ratio);
}

void	assign_rgb(int *flag, t_rgb *obj, char *str)
{
	char	**arr;

	if (ft_isrgb(str) == 0)
	{
		*flag = -1;
		return ;
	}
	arr = ft_split(str, ',');
	obj->red = ft_atoi(arr[0]);
	obj->green = ft_atoi(arr[1]);
	obj->blue = ft_atoi(arr[2]);
	free_split(arr);
	if (!(ft_inrange(obj->red, 0, 255) && ft_inrange(obj->green, 0, 255)
		&& ft_inrange(obj->blue, 0, 255)))
		*flag = -1;
}

void	assign_coord(int *flag, t_coord *obj, char *str)
{
	char	**arr;
	int		i;
	double	*temp;

	arr = ft_split(str, ',');
	if (ft_arrlen(arr) != 4)
		*flag = -1;
	else
	{
		temp = ft_calloc(4, sizeof(double));
		i = -1;
		while (++i < 3)
		{
			if (ft_isdouble(arr[i]) == 0)
			{
				*flag = -1;
				break ;
			}
			temp[i] = ft_atod(arr[i]);
		}
		set_coord(obj, temp);
		free(temp);
	}
	free_split(arr);
}

void	assign_vector(int *flag, t_coord *obj, char *str)
{
	assign_coord(flag, obj, str);
	if (*flag == -1)
		return ;
	if (!(ft_inrange(obj->x, -1, 1) && ft_inrange(obj->y, -1, 1)
		&& ft_inrange(obj->z, -1, 1)))
		*flag = -1;
}

double	assign_fov(int *flag, char *str)
{
	double	fov;

	if (ft_isdouble(str) == 0)
		*flag = -1;
	fov = ft_atod(str);
	if (ft_inrange(fov, 0, 180) == 0)
		*flag = -1;
	return (fov);
}