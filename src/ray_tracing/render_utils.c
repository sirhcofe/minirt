/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:27:01 by jthor             #+#    #+#             */
/*   Updated: 2024/01/11 20:09:01 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*get_object(t_list *obj_lst, int index)
{
	int	iter;

	iter = -1;
	while (++iter < index)
		obj_lst = obj_lst->next;
	return ((t_object *)obj_lst->content);
}

t_coord	get_intsct_point(t_object *node)
{
	if (node->e_idx == sp)
		return (node->obj.sphere.intsct);
	else if (node->e_idx == pl)
		return (node->obj.plane.intsct);
	else
		return (node->obj.cylinder.intsct);
}

t_rgb	get_colour(t_object *obj)
{
	if (obj->e_idx == sp)
		return (obj->obj.sphere.colour);
	else if (obj->e_idx == pl)
		return (obj->obj.plane.colour);
	else
		return (obj->obj.cylinder.colour);
}

t_coord    get_cy_normal(t_cy obj, t_coord intsct)
{
	double	dist;
	t_coord	cross_res;
	t_coord	p2p_vector;
	t_coord	projection;
	t_coord	subtract_projection;

	if (obj.intsct_type == 1) // curved surface
	{
		p2p_vector = vect_subt(intsct, obj.center);
		projection = vect_mult(obj.axis_vector, dot_prod(p2p_vector, obj.axis_vector) / dot_prod(obj.axis_vector, obj.axis_vector));
		subtract_projection = normalize(vect_subt(p2p_vector, projection));
		return (subtract_projection);
	}
	else if (obj.intsct_type == 2) // top end cap
		return (obj.axis_vector);
	else if (obj.intsct_type == 3) // bottom end cap
		return (vect_mult(obj.axis_vector, -1));
	else
		return (intsct);
}

t_coord	get_normal(t_object *obj, t_coord intsct, t_coord to_light)
{
	t_coord	normal;

	if (obj->e_idx == sp)
		normal = normalize(vect_subt(intsct, obj->obj.sphere.center));
	else if (obj->e_idx == pl)
		normal = obj->obj.plane.normal_vector;
	else
		normal = get_cy_normal(obj->obj.cylinder, intsct);
	return (normal);
}
