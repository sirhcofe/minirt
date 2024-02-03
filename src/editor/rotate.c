/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:32:27 by jthor             #+#    #+#             */
/*   Updated: 2024/02/03 15:54:26 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rotate_obj(t_minirt *rt, int key, t_coord world_coord[3])
{
	double	angle;
	t_coord	axis;

	if (key == W || key == A || key == Z)
		angle = -0.174533;
	else if (key == S || key == D || key == C)
		angle = 0.174533;
	if (key == W || key == S)
		axis = world_coord[0];
	else if (key == A || key == D)
		axis = world_coord[1];
	else if (key == Z || key == C)
		axis = world_coord[2];
	if (rt->editor.target->e_idx == cy)
		rotate_cylinder(&rt->editor.target->obj.cylinder, axis, angle);
	else if (rt->editor.target->e_idx == pl)
		rotate_plane(&rt->editor.target->obj.plane, axis, angle);
	else if (rt->editor.target->e_idx == co)
		rotate_cone(&rt->editor.target->obj.cone, axis, angle);
	print_editor(rt);
	mlx_clear_window(rt->mlx, rt->mlx_win);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
}

void	rotate_along_axis(t_cam *camera, t_coord axis, int key)
{
	double	angle;

	if (key == W || key == A || key == Z)
		angle = -0.174533;
	else if (key == S || key == D || key == C)
		angle = 0.174533;
	camera->look = normalize(rotation(&camera->look, angle, axis));
	camera->up = normalize(rotation(&camera->up, angle, axis));
	camera->right = normalize(rotation(&camera->right, angle, axis));
}

void	rotate_cam(t_minirt *rt, int key, t_coord world_coord[3])
{
	if (key == W || key == S)
		rotate_along_axis(&rt->file_data->camera, world_coord[0], key);
	else if (key == A || key == D)
		rotate_along_axis(&rt->file_data->camera, world_coord[1], key);
	else if (key == Z || key == C)
		rotate_along_axis(&rt->file_data->camera, world_coord[2], key);
	print_editor(rt);
	mlx_clear_window(rt->mlx, rt->mlx_win);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
}

void	key_rotate(t_minirt *rt, int key)
{
	t_coord	world_coord[3];

	set_coord(&world_coord[0], 1, 0, 0);
	set_coord(&world_coord[1], 0, 1, 0);
	set_coord(&world_coord[2], 0, 0, 1);
	if (rt->editor.flag == CAM_EDIT)
		rotate_cam(rt, key, world_coord);
	else if (rt ->editor.flag == OBJ_EDIT)
		rotate_obj(rt, key, world_coord);
	else
		return ;
}
