/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:12:58 by chenlee           #+#    #+#             */
/*   Updated: 2024/02/03 18:08:36 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rotate_cylinder(t_cy *cy, t_coord axis, double angle)
{
	cy->axis_vector = normalize(rotation(&cy->axis_vector, angle, axis));
}

void	rotate_plane(t_pl *pl, t_coord axis, double angle)
{
	pl->normal_vector = normalize(rotation(&pl->normal_vector, angle, axis));
}

void	rotate_cone(t_co *co, t_coord axis, double angle)
{
	t_coord	midpoint;
	t_coord	vert_offset;
	t_coord	base_offset;

	midpoint = vect_div(vect_add(co->vertex, co->base_center), 2);
	vert_offset = vect_subt(co->vertex, midpoint);
	base_offset = vect_subt(co->base_center, midpoint);
	co->axis_vector = normalize(rotation(&co->axis_vector, angle, axis));
	vert_offset = rotation(&vert_offset, angle, axis);
	base_offset = rotation(&base_offset, angle, axis);
	co->vertex = vect_add(midpoint, vert_offset);
	co->base_center = vect_add(midpoint, base_offset);
}
