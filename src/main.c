/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:31:29 by chenlee           #+#    #+#             */
/*   Updated: 2023/11/03 22:04:35 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	arg_check(int argc, char **argv)
{
	char	*period;

	if (argc != 2)
		arg_error("Usage: ./miniRT <MAP FILE>\n");
	period = ft_strchr(argv[1], '.');
	if (!period)
		arg_error("Invalid map file.\n");
	if (ft_strncmp(period, ".rt", 4) != 0)
		arg_error("Invalid map file.\n");
}

t_coord	init_vector(double x, double y, double z)
{
	t_coord	res;

	res.x = x;
	res.y = y;
	res.z = z;
	res.w = 1;
	return (res);
}

t_rgb	init_colour(unsigned char r, unsigned char g, unsigned char b)
{
	t_rgb	res;

	res.red = r;
	res.green = g;
	res.blue = b;
}

void	put_pxl(t_minirt *rt, int x, int y, int colour)
{
	char	*dst;

	dst = rt->addr + (y * rt->line_len + x * (rt->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

int	create_colour(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	is_zero_too(t_coord vector)
{
	int	coord_not_zero;

	coord_not_zero = 0;
	if (vector.x > 0.00001 || vector.x < -0.00001)
		coord_not_zero++;
	if (vector.y > 0.00001 || vector.y < -0.00001)
		coord_not_zero++;
	if (vector.z > 0.00001 || vector.y < -0.00001)
		coord_not_zero++;
	if (coord_not_zero == 0)
		return (1);
	else
		return (0);
}

void	calc_camera(t_cam *camera)
{
	t_coord	world_coord[3];
	t_coord	rot_axis;

	world_coord[0] = init_vector(1, 0, 0);
	world_coord[1] = init_vector(0, 1, 0);
	world_coord[2] = init_vector(0, 0, 1);
	rot_axis = cross_prod(world_coord[2], camera->look);
	if (is_zero_too(rot_axis))
	{
		if (camera->look.z <= -0.0001)
			camera->right = vect_mult(world_coord[0], -1.0);
		else
			camera->right = world_coord[0];
		camera->up = world_coord[1];
	}
	else
	{
		camera->up = rot_axis;
		camera->right = cross_prod(camera->up, camera->look);
	}
}

int	main(int argc, char **argv)
{
	t_minirt	*rt;
	t_cy		cylinder;
	t_sp		sphere;
	t_pl		plane;

	// arg_check(argc, argv);
	rt = init_mlx_window();
	// rt->file_data = parse_file(argv[1]);

	t_cam	camera;
	camera.fov = 1.0472;
	camera.point = init_vector(0, 0, 5);
	camera.look = normalize(init_vector(0, 0, 1));
	calc_camera(&camera);

	cylinder.center = init_vector(0, 0, 20);
	cylinder.axis_vector = normalize(init_vector(10, 0, 10));
	cylinder.colour = init_colour(0, 186, 188);
	cylinder.radius = 3;
	cylinder.height = 4;

	sphere.center = init_vector(0, 0, 0);
	sphere.colour = init_colour(255, 0, 0);
	sphere.dia = 5;

	plane.normal_vector = init_vector(0.5, 0.2, 0.3);
	plane.point = init_vector(10, 2, 0);

	double	increment = camera.fov / rt->width;
	double	random;
	double	check;
	t_coord	offset;
	t_coord	ray_vector;

	int	i;
	int	j;
	i = 0;
	while (i < rt->height)
	{
		offset = rotation(&camera.look, increment * (i - rt->height / 2), camera.right);
		j = 0;
		while (j < rt->width)
		{
			ray_vector = rotation(&offset, increment * (j - rt->width / 2), camera.up);
			// if (!isinf(cy_intersection(ray_vector, camera.point, &cylinder)))
			check = cy_intersection(ray_vector, camera.point, &cylinder);
			if (!isinf(check))
				put_pxl(rt, j, i, create_colour(0, 255, 0, 0));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
	set_controls(rt);
	mlx_loop(rt->mlx);
}
