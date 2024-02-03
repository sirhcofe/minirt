/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_normal_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:55:52 by chenlee           #+#    #+#             */
/*   Updated: 2024/01/30 19:15:37 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// FOR getting cone/cylinder normal
// intsct_type == 1: curved surface
// intsct_type == 2: top end cap (or end cap for cone)
// intsct_type == 3: bottom end cap - only for cylinder

t_coord	get_co_normal(t_co obj, t_coord intsct)
{
	double	slant_height_angle[2];
	double	dist_vert_to_intsct;
	double	dist_axis_perp_intsct;
	t_coord	point_on_axis;
	t_coord	normal;

	if (obj.intsct_type == 1)
	{
		slant_height_angle[0] = sqrt(pow(obj.radius, 2) + pow(obj.height, 2));
		slant_height_angle[1] = atan(obj.radius / obj.height);
		dist_vert_to_intsct = vect_magnitude(obj.intsct, obj.vertex);
		dist_axis_perp_intsct = dist_vert_to_intsct
			/ cos(slant_height_angle[1]);
		point_on_axis = vect_add(obj.vertex,
				vect_mult(obj.axis_vector, dist_axis_perp_intsct));
		normal = normalize(vect_subt(intsct, point_on_axis));
		return (normal);
	}
	else
		return (obj.axis_vector);
}

t_coord	get_cy_normal(t_cy obj, t_coord intsct, t_coord axis_v)
{
	t_coord	p2p_vector;
	t_coord	projection;
	t_coord	subtract_projection;

	if (obj.intsct_type == 1)
	{
		p2p_vector = vect_subt(intsct, obj.center);
		projection = vect_mult(axis_v,
				dot_prod(p2p_vector, axis_v) / dot_prod(axis_v, axis_v));
		subtract_projection = normalize(vect_subt(p2p_vector, projection));
		return (subtract_projection);
	}
	else if (obj.intsct_type == 2)
		return (axis_v);
	else if (obj.intsct_type == 3)
		return (vect_mult(axis_v, -1));
	else
		return (intsct);
}

t_coord	get_normal(t_object *obj, t_coord intsct, t_coord from_cam)
{
	t_coord	normal;

	if (obj->e_idx == sp)
		normal = normalize(vect_subt(intsct, obj->obj.sphere.center));
	else if (obj->e_idx == pl)
		normal = obj->obj.plane.normal_vector;
	else if (obj->e_idx == cy)
		normal = get_cy_normal(obj->obj.cylinder, intsct,
				obj->obj.cylinder.axis_vector);
	else
		normal = get_co_normal(obj->obj.cone, intsct);
	if (dot_prod(from_cam, normal) >= 0)
		normal = vect_mult(normal, -1);
	return (normal);
}
