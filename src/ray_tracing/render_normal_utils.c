/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_normal_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:55:52 by chenlee           #+#    #+#             */
/*   Updated: 2024/01/22 19:45:44 by chenlee          ###   ########.fr       */
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
void	back_to_global(t_coord *normal_vector, t_coord rot_axis, double rot_angle, t_coord mid_point)
{
	t_coord	offset;
	t_coord	tf_normal;

	offset = vect_subt(*normal_vector, mid_point);
	tf_normal = rotation(&offset, -rot_angle, rot_axis);
	tf_normal = vect_add(tf_normal, mid_point);
	normal_vector = &tf_normal;
}

/**
 * Function aligns the cone with the Z-axis to simplify the normal calculations.
 * @param tf The transformed vector, whereby [0]: transformed intersection
 * point; [1]: transformed cone vertex coordinates
 * @param intsct The intersection point on the cone object.
 * @param obj The cone object.
*/
// t_coord	align_co_z(t_coord tf[2], t_coord intsct, t_co obj, double *rot_angle)
t_coord	*align_co_z(t_co obj, t_coord intsct, t_coord *axis, double *angle)
{
	t_coord	z_axis;
	t_coord	mid_point;
	t_coord	offset;
	t_coord	*tf;

	set_coord(&z_axis, 0, 0, 1);
	*axis = normalize(cross_prod(obj.axis_vector, z_axis));
	tf = malloc(sizeof(t_coord) * 3);
	if (is_zero_vector(*axis))
	{
		tf[0] = intsct;
		tf[1] = obj.vertex;
	}
	else
	{
		*angle = acos(dot_prod(obj.axis_vector, z_axis));
		tf[0] = rotation(&intsct, *angle, *axis);
		mid_point = vect_div(vect_add(obj.base_center, obj.vertex), 2);
		offset = vect_subt(obj.vertex, mid_point);
		tf[1] = rotation(&offset, *angle, *axis);
		tf[1] = vect_add(tf[1], mid_point);
		tf[2] = mid_point;
	}
	return (tf);
}

// FOR getting cone/cylinder normal
// intsct_type == 1: curved surface
// intsct_type == 2: top end cap (or end cap for cone)
// intsct_type == 3: bottom end cap - only for cylinder

t_coord	get_co_normal(t_co obj, t_coord intsct)
{
	double	slant_height;
	double	rot_angle;
	t_coord	rot_axis;
	t_coord	*tf_intsct_vert_mid;
	t_coord	rad_norm_vect[2];

	if (obj.intsct_type == 1) // curved surface
	{
		tf_intsct_vert_mid = align_co_z(obj, intsct, &rot_axis, &rot_angle);
		slant_height = sqrt(pow(obj.height, 2) + pow(obj.radius, 2));
		rad_norm_vect[0].x = tf_intsct_vert_mid[0].x - tf_intsct_vert_mid[1].x;
		rad_norm_vect[0].y = tf_intsct_vert_mid[0].y - tf_intsct_vert_mid[1].y;
		rad_norm_vect[1].x = rad_norm_vect[0].x * (obj.height / slant_height);
		rad_norm_vect[1].y = rad_norm_vect[0].y * (obj.height / slant_height);
		rad_norm_vect[1].z = -sqrt(pow(rad_norm_vect[0].x, 2)
									+ pow(rad_norm_vect[0].y, 2))
							* (obj.radius / obj.height);
		if (!is_zero_vector(rot_axis))
			back_to_global(&rad_norm_vect[1], rot_axis, rot_angle,
								tf_intsct_vert_mid[2]);
		free(tf_intsct_vert_mid);
		rad_norm_vect[1] = normalize(rad_norm_vect[1]);
		printf("normal %f %f %f\n", rad_norm_vect[1].x, rad_norm_vect[1].y, rad_norm_vect[1].z);
		// return (normalize(rad_norm_vect[1]));
		return (rad_norm_vect[1]);
	}
	else // end cap
		return (obj.axis_vector);
}

t_coord    get_cy_normal(t_cy obj, t_coord intsct)
{
	double	dist;
	t_coord	cross_res;
	t_coord	p2p_vector;
	t_coord	projection;
	t_coord	subtract_projection;

	if (obj.intsct_type == 1)
	{
		p2p_vector = vect_subt(intsct, obj.center);
		projection = vect_mult(obj.axis_vector,
									dot_prod(p2p_vector, obj.axis_vector)
							/ dot_prod(obj.axis_vector, obj.axis_vector));
		subtract_projection = normalize(vect_subt(p2p_vector, projection));
		return (subtract_projection);
	}
	else if (obj.intsct_type == 2)
		return (obj.axis_vector);
	else if (obj.intsct_type == 3)
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
	else if (obj->e_idx == cy)
		normal = get_cy_normal(obj->obj.cylinder, intsct);
	else
		normal = get_co_normal(obj->obj.cone, intsct);
	return (normal);
}
