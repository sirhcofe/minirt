/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:32:27 by jthor             #+#    #+#             */
/*   Updated: 2024/02/02 23:40:56 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rotate_cam(t_minirt *rt, int key)
{
	t_coord	*point;

	point = &rt->file_data->camera.look;
	if (key == A)
		*point = rotation(point, -0.174533, rt->file_data->camera.up);
	else if (key == D)
		*point = rotation(point, 0.174533, rt->file_data->camera.up);
	else if (key == W)
		*point = rotation(point, -0.174533, rt->file_data->camera.right);
	else if (key == S)
		*point = rotation(point, 0.174533, rt->file_data->camera.right);
	*point = normalize(*point);
	print_editor(rt);
	mlx_clear_window(rt->mlx, rt->mlx_win);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
}

void	key_rotate(t_minirt *rt, int key)
{
	if (rt->editor.flag == CAM_EDIT)
		rotate_cam(rt, key);
	else
		return ;
	// else if (rt ->editor.flag == OBJ_EDIT)
	// 	rotate_obj(rt, key);
}
