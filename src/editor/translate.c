/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:32:36 by jthor             #+#    #+#             */
/*   Updated: 2024/02/02 22:31:09 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	translate_cam(t_minirt *rt, int key)
{
	if (key == UP)
		rt->file_data->camera.point.y += 1;
	else if (key == DOWN)
		rt->file_data->camera.point.y -= 1;
	else if (key == LEFT)
		rt->file_data->camera.point.x -= 1;
	else if (key == RIGHT)
		rt->file_data->camera.point.x += 1;
	else if (key == R_SQRB)
		rt->file_data->camera.point.z += 1;
	else if (key == L_SQRB)
		rt->file_data->camera.point.z -= 1;
	print_editor(rt);
	mlx_clear_window(rt->mlx, rt->mlx_win);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
}

void	translate_light(t_minirt *rt, int key)
{
	if (key == UP)
		rt->file_data->light.point.y += 1;
	else if (key == DOWN)
		rt->file_data->light.point.y -= 1;
	else if (key == LEFT)
		rt->file_data->light.point.x -= 1;
	else if (key == RIGHT)
		rt->file_data->light.point.x += 1;
	else if (key == R_SQRB)
		rt->file_data->light.point.z += 1;
	else if (key == L_SQRB)
		rt->file_data->light.point.z -= 1;
	print_editor(rt);
	mlx_clear_window(rt->mlx, rt->mlx_win);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
}

t_coord	*get_object_point(t_object *obj)
{
	if (obj->e_idx == sp)
		return (&(obj->obj.sphere.center));
	else if (obj->e_idx == pl)
		return (&(obj->obj.plane.point));
	else if (obj->e_idx == cy)
		return (&(obj->obj.cylinder.center));
	else
		return (&(obj->obj.cone.base_center));
}

void	translate_obj(t_minirt *rt, int key)
{
	t_coord	*obj_point;

	obj_point = get_object_point(rt->editor.target);
	if (key == UP)
		obj_point->y += 1;
	else if (key == DOWN)
		obj_point->y -= 1;
	else if (key == LEFT)
		obj_point->x -= 1;
	else if (key == RIGHT)
		obj_point->x += 1;
	else if (key == R_SQRB)
		obj_point->z += 1;
	else if (key == L_SQRB)
		obj_point->z -= 1;
	print_editor(rt);
	mlx_clear_window(rt->mlx, rt->mlx_win);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
}

void	key_translate(t_minirt *rt, int key)
{
	if (rt->editor.flag == EDIT_MODE)
		return ;
	else if (rt->editor.flag == CAM_EDIT)
		translate_cam(rt, key);
	else if (rt->editor.flag == LIGHT_EDIT)
		translate_light(rt, key);
	else if (rt->editor.flag == OBJ_EDIT)
		translate_obj(rt, key);
}
