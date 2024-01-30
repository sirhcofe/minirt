/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_normal_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:55:52 by chenlee           #+#    #+#             */
/*   Updated: 2024/01/19 15:02:08 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Function rotates the calculated normal vector back to the original
 * orientation of the cone.
 * @param normal_vector The calculated normal vector
 * @param rot_axis The rotation axis
 * @param obj The cone object
*/
void	back_to_global(t_coord normal_vector, t_coord rot_axis, t_co obj)
{
	t_coord	z_axis;
	t_coord	tf_normal;
	double	rot_angle;

	set_coord(&z_axis, 0, 0, 1);
	rot_angle = acos(dot_prod(obj.axis_vector, z_axis));
	tf_normal = rotation(&normal_vector, -rot_angle, rot_axis);
	normal_vector = tf_normal;
}

/**
 * Function aligns the cone with the Z-axis to simplify the normal calculations.
 * @param tf The transformed vector, whereby [0]: transformed intersection
 * point; [1]: transformed cone vertex coordinates
 * @param intsct The intersection point on the cone object.
 * @param obj The cone object.
*/
t_coord	align_co_z(t_coord tf[2], t_coord intsct, t_co obj)
{
	t_coord	z_axis;
	t_coord	rot_axis;
	double	rot_angle;

	set_coord(&z_axis, 0, 0, 1);
	rot_axis = normalize(cross_prod(obj.axis_vector, z_axis));
	if (is_zero_vector(rot_axis))
	{
		tf[0] = intsct;
		tf[1] = obj.vertex;
	}
	else
	{
		rot_angle = acos(dot_prod(obj.axis_vector, z_axis));
		tf[0] = rotation(&intsct, rot_angle, rot_axis);
		tf[1] = rotation(&obj.vertex, rot_angle, rot_axis);
	}
	return (rot_axis);
}

// FOR getting cone/cylinder normal
// intsct_type == 1: curved surface
// intsct_type == 2: top end cap (or end cap for cone)
// intsct_type == 3: bottom end cap - only for cylinder

t_coord	get_co_normal(t_co obj, t_coord intsct)
{
	double	slant_height;
	t_coord	rotation_axis;
	t_coord	radial_vector;
	t_coord	normal_vector;
	t_coord	transformed[2];

	if (obj.intsct_type == 1)
	{
		rotation_axis = align_co_z(transformed, intsct, obj);
		slant_height = sqrt(pow(obj.height, 2) + pow(obj.radius, 2));
		radial_vector.x = transformed[0].x - transformed[1].x;
		radial_vector.y = transformed[0].y - transformed[1].y;
		radial_vector.z = 0;
		normal_vector.x = radial_vector.x * (obj.height / slant_height);
		normal_vector.y = radial_vector.y * (obj.height / slant_height);
		normal_vector.z = -obj.radius * (obj.height / slant_height);
		if (!is_zero_vector(rotation_axis))
			back_to_global(normal_vector, rotation_axis, obj);
		return (normalize(normal_vector));
	}
	else
		return (obj.axis_vector);
}

t_coord	get_cy_normal(t_cy obj, t_coord intsct, t_coord axis_v)
{
	double	dist;
	t_coord	cross_res;
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

t_coord	get_normal(t_object *obj, t_coord intsct, t_coord to_light)
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
	return (normal);
}
