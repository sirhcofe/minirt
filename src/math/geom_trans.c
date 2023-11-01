/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geom_trans.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:52:10 by chenlee           #+#    #+#             */
/*   Updated: 2023/10/27 21:56:28 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_coord(t_coord *obj, double x, double y, double z)
{
	obj->x = x;
	obj->y = y;
	obj->z = z;
	obj->w = 1.0;
}

t_coord	translation(t_coord object)
{
	t_coord	transl_vector;

	transl_vector.x = 0 - object.x;
	transl_vector.y = 0 - object.y;
	transl_vector.z = 0 - object.z;
	transl_vector.w = object.w;
	return (transl_vector);
}

t_coord	rotation(t_coord *vector, double angle, t_coord axis)
{
	t_coord	rot_vect;
	t_coord	a;
	t_coord	b;
	t_coord	c;

	a = vect_mult(*vector, cos(angle));
	b = vect_mult(cross_prod(axis, *vector), sin(angle));
	c = vect_mult(axis, (dot_prod(axis, *vector) * (1 - cos(angle))));
	rot_vect = vect_add(a, vect_add(b, c));
	return (rot_vect);
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