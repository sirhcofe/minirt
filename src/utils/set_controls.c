/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 00:06:02 by chenlee           #+#    #+#             */
/*   Updated: 2023/09/08 16:23:03 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_program(t_minirt *rt)
{
	free_data(rt);
	exit(0);
}

void	ft_img_refresh(t_minirt *rt)
{
	mlx_destroy_image(rt->mlx, rt->img);
	rt->img = mlx_new_image(rt->mlx, rt->width, rt->height);
	rt->addr = mlx_get_data_addr(rt->img, &(rt->bits_per_pixel),
			&(rt->line_len), &rt->endian);
}

void	rotate_cam(t_minirt *rt, int key)
{
	t_coord	x_axis;
	t_coord	y_axis;
	t_coord	z_axis;
	double	interval;

	// setcoord here for x, y, z axis
	set_coord(&y_axis, 1, 0, 0);
	interval = 0.174533;
	if (key == MAC_RIGHT)
		rt->file_data->camera.look = normalize(rotation(&rt->file_data->camera.look, interval, y_axis));
	print_image(rt);
	mlx_clear_window(rt->mlx, rt->mlx_win);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
}

void	translate_cam(t_minirt *rt, int key)
{
	if (key == MAC_UP)
		rt->file_data->camera.point.y += 1;
	else if (key == MAC_DOWN)
		rt->file_data->camera.point.y -= 1;
	else if (key == MAC_LEFT)
		rt->file_data->camera.point.x -= 1;
	else if (key == MAC_RIGHT)
		rt->file_data->camera.point.x += 1;
	print_image(rt);
	mlx_clear_window(rt->mlx, rt->mlx_win);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
}

int	key_press(int key, t_minirt *rt)
{
	ft_img_refresh(rt);
	if (key == MAC_ESC || key == WIN_ESC)
		close_program(rt);
	if (key == MAC_UP || key == MAC_DOWN || key == MAC_LEFT
		|| key == MAC_RIGHT)		
		translate_cam(rt, key);
	return (0);
}

void	set_controls(t_minirt *rt)
{
	mlx_key_hook(rt->mlx_win, key_press, rt);
	mlx_hook(rt->mlx_win, 17, 0, close_program, rt);
}
