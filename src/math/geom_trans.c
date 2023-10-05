/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geom_trans.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:52:10 by chenlee           #+#    #+#             */
/*   Updated: 2023/09/17 23:45:32 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	translation(t_coord object)
{
	t_coord	transl_vector;

	transl_vector.x = 0 - object.x;
	transl_vector.y = 0 - object.y;
	transl_vector.z = 0 - object.z;
	transl_vector.w = object.w;
	return (transl_vector);
}

t_coord	rotation(t_coord *vector, double angle)
{
	t_coord	z_axis;
	t_coord	rot_vect;

	set_coord(&z_axis, 0.0, 0.0, 1.0);
	rot_vect = vect_add(vect_mult(*vector, cos(angle)),
				vect_add(vect_mult(cross_prod(&z_axis, vector), sin(angle)),
						vect_mult(vect_mult(z_axis, dot_prod(&z_axis, vector)),
								(1 - cos(angle)))));
}

/**
 * v' = v * cos(θ) + (k x v) * sin(θ) + k * (k ⋅ v) * (1 - cos(θ))
 * Where:
 * v is the original vector.
 * k is the unit vector representing the axis of rotation.
 * θ is the angle of rotation in radians.
 * x denotes the cross product of two vectors.
 * ⋅ denotes the dot product of two vectors.
*/