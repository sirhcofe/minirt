/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:32:27 by jthor             #+#    #+#             */
/*   Updated: 2024/01/31 10:32:28 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rotate_cam(t_minirt *rt, int key)
{
	t_coord	axis;
	double	interval;

	// setcoord here for x, y, z axis
	set_coord(&axis, 1, 0, 0);
	interval = 0.174533;
	if (key == MAC_RIGHT)
		rt->file_data->camera.look = normalize(rotation(&rt->file_data->camera.look, interval, axis));
	print_image(rt);
	mlx_clear_window(rt->mlx, rt->mlx_win);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
}
