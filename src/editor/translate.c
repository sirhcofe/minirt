/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:32:36 by jthor             #+#    #+#             */
/*   Updated: 2024/02/03 17:50:08 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_coord	*determine_target(t_minirt *rt)
{
	if (rt->editor.flag == CAM_EDIT)
		return (&(rt->file_data->camera.point));
	else if (rt->editor.flag == LIGHT_EDIT)
		return (&(rt->file_data->light.point));
	else if (rt->editor.flag == OBJ_EDIT)
		return (get_object_point(rt->editor.target));
	else
		return (NULL);
}

void	translate_point(t_coord *point, int key)
{
	if (key == UP)
		point->y += 1.5;
	else if (key == DOWN)
		point->y -= 1.5;
	else if (key == LEFT)
		point->x -= 1.5;
	else if (key == RIGHT)
		point->x += 1.5;
	else if (key == R_SQRB)
		point->z += 1.5;
	else if (key == L_SQRB)
		point->z -= 1.5;
}

void	key_translate(t_minirt *rt, int key)
{
	t_coord	*target_point;

	if (rt->editor.flag == NOT_EDIT)
		return ;
	target_point = determine_target(rt);
	translate_point(target_point, key);
	if (rt->editor.flag == OBJ_EDIT && rt->editor.target->e_idx == co)
		translate_point(&(rt->editor.target->obj.cone.vertex), key);
	print_editor(rt);
	mlx_clear_window(rt->mlx, rt->mlx_win);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
}
