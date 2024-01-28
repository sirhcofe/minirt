/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 01:06:55 by chenlee           #+#    #+#             */
/*   Updated: 2024/01/19 15:10:40 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Function calculates the closest intersection distance of a ray with a cone,
 * considering both the conical surface and the endcap
 * @param transltd Translated origin and direction vector of the ray
 * @param cone The cone object
 * @return The closest intersection distance. Returns INFINITY if no
 * intersection occurs
*/
double	calc_co_intersection(t_coord transltd[2], t_co *cone)
{
	double	lat_dist;
	double	endcap_dist;

	conical_intsct(&lat_dist, transltd, cone);
	co_endcap_intsct(&endcap_dist, transltd, cone);
	if (isinf(lat_dist) && isinf(endcap_dist))
		return (INFINITY);
	else if (lat_dist < endcap_dist)
	{
		cone->intsct_type = 1;
		return (lat_dist);
	}
	else
		return (endcap_dist);
}

/**
 * Transforms the ray to the cone's local coordinate space
 * @param translatd Direction vector of the ray
 * @param origin Origin of the ray
 * @param co The cone object
 * @return Function does not return
*/
void	to_co_space(t_coord translatd[2], t_coord ray, t_coord origin, t_co *co)
{
	t_coord	offset;
	t_coord	z_axis;
	t_coord	rot_axis;
	double	rot_angle;

	set_coord(&offset, 0, 0, 0);
	set_coord(&z_axis, 0, 0, 1);
	translatd[ori] = vect_add(origin, vect_subt(offset, co->vertex));
	rot_axis = normalize(cross_prod(co->axis_vector, z_axis));
	if (is_zero_vector(rot_axis))
		translatd[vec] = ray;
	else
	{
		rot_angle = acos(dot_prod(co->axis_vector, z_axis));
		translatd[ori] = rotation(&translatd[ori], rot_angle, rot_axis);
		translatd[vec] = rotation(&ray, rot_angle, rot_axis);
	}
}

double	co_intersection(t_coord ray_vec, t_coord origin, t_co *co)
{
	t_coord	transltd[2];
	double	dist;

	to_co_space(transltd, ray_vec, origin, co);
	dist = calc_co_intersection(transltd, co);
	if (!isinf(dist))
		co->intsct = vect_add(origin, vect_mult(ray_vec, dist));
	return (dist);
}
