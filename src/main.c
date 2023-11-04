/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:31:29 by chenlee           #+#    #+#             */
/*   Updated: 2023/11/04 21:18:31 by chenlee          ###   ########.fr       */
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

void	calc_camera(t_cam *camera)
{
	t_coord	world_coord[3];
	t_coord	rot_axis;

	set_coord(&world_coord[0], 1, 0, 0);
	set_coord(&world_coord[1], 0, 1, 0);
	set_coord(&world_coord[2], 0, 0, 1);
	// world_coord[0] = init_vector(1, 0, 0);
	// world_coord[1] = init_vector(0, 1, 0);
	// world_coord[2] = init_vector(0, 0, 1);
	rot_axis = cross_prod(world_coord[2], camera->look);
	if (is_zero_vector(rot_axis))
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
	camera.point = init_vector(0, 0, 0);
	camera.look = normalize(init_vector(0, 0, 1));
	calc_camera(&camera);

	// dprintf(2, "look=%f %f %f\n", camera.look.x, camera.look.y, camera.look.z);
	// dprintf(2, "up=%f %f %f\n", camera.up.x, camera.up.y, camera.up.z);
	// dprintf(2, "right=%f %f %f\n", camera.right.x, camera.right.y, camera.right.z);

	sphere.center = init_vector(-5, -1, 15);
	sphere.colour = init_colour(255, 0, 0);
	sphere.dia = 4;

	cylinder.center = init_vector(0, 0, 22);
	cylinder.axis_vector = normalize(init_vector(-8, 0, 10));
	cylinder.colour = init_colour(0, 186, 188);
	cylinder.radius = 3;
	cylinder.height = 10;

	plane.normal_vector = normalize(init_vector(0, 100, 1));
	plane.point = init_vector(0, -20, 25);

	double	increment = camera.fov / rt->width;
	double	random;
	double	check;
	double	check2;
	double	check3;
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
			check = sp_intersection(ray_vector, camera.point, &sphere);
			check2 = cy_intersection(ray_vector, camera.point, &cylinder);
			check3 = pl_intersection(ray_vector, camera.point, &plane);
			if (isinf(check) && isinf(check2) && isinf(check3))
				;
			else if (check <= check2 && check <= check3)
				put_pxl(rt, j, i, create_colour(0, 255, 0, 0));
			else if (check2 < check && check2 <= check3)
				put_pxl(rt, j, i, create_colour(0, 0, 255, 0));
			else
				put_pxl(rt, j, i, create_colour(0, 0, 0, 255));
			// if (!isinf(check))
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
	set_controls(rt);
	mlx_loop(rt->mlx);
}
